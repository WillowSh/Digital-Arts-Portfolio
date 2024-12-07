#include "hw3.h"
#include "3rdparty/glad.h" // needs to be included before GLFW!
#include "3rdparty/glfw/include/GLFW/glfw3.h"
#include "hw3_scenes.h"
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "3rdparty/stb_image.h"


using namespace hw3;


void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void processInput2(GLFWwindow *window, Vector3 &position, Vector3 direction, Vector3 up, Vector3 right, float deltaTime) {
    double speed = 0.01f * deltaTime; // Adjust speed as needed

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += speed * direction; // Move forward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= speed * direction; // Move backward
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= right * speed; // Move left
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += right * speed; // Move right
    // Optionally, add vertical movement:
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        position += up * speed; // Move up
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        position -= up * speed; // Move down
}


bool isRotating = true; // 初始设定为旋转
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        isRotating = !isRotating; // 切换旋转状态
    }
}

GLFWwindow* initOpenGL() {
    // Initialize GLFW, GLEW, create a window, etc.
    glfwInit();

    // 设置 GLFW 使用的 OpenGL 版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1000, 800, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;;
    }
    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    // 初始化 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;;
    }

    return window;
}

unsigned int compileShader(GLenum shaderType, const char* shaderSource) {
    // Create a shader object
    unsigned int shader = glCreateShader(shaderType);

    // Attach the shader source code to the shader object and compile the shader
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    // Check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0; // or handle the error in a way that's appropriate for your application
    }

    return shader;
}
void printMatrix(const glm::mat4 &mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
unsigned int linkShaderProgram(unsigned int vertexShader, unsigned int fragmentShader) {
    // Create a program object
    unsigned int shaderProgram = glCreateProgram();

    // Attach shaders to the program and link them
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return 0; // or handle the error in a way that's appropriate for your application
    }

    // After linking, shaders can be detached and deleted as they're no longer needed
    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void setShaderMatrix(unsigned int shaderProgram, const std::string& uniformName, const glm::mat4& matrix) {
    // Activate the shader program
    glUseProgram(shaderProgram);

    // Get the location of the uniform variable
    int uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());

    // Check if the uniform location is valid
    if (uniformLocation == -1) {
        std::cerr << "Warning: Could not find uniform " << uniformName << std::endl;
        return;
    }

    // Set the uniform value
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

unsigned int loadTexture(const char* path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // 设置纹理参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 加载图像
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format = GL_RGB;
        if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return textureID;
}


struct MeshOpenGLData {
    unsigned int vao;             // Vertex Array Object
    unsigned int vboVertices;     // Vertex Buffer Object for vertices
    unsigned int vboColors;       // Vertex Buffer Object for vertex colors
    unsigned int vboNormals;
    unsigned int ebo;             // Element Buffer Object for indices
    unsigned int vboUV;
    unsigned int textureID;
};

void cleanup(const std::vector<MeshOpenGLData>& meshData) {
    for (const auto& glData : meshData) {
        // Delete VAO
        if (glData.vao != 0) {
            glDeleteVertexArrays(1, &glData.vao);
        }

        // Delete VBOs
        if (glData.vboVertices != 0) {
            glDeleteBuffers(1, &glData.vboVertices);
        }
        if (glData.vboColors != 0) {
            glDeleteBuffers(1, &glData.vboColors);
        }
        if (glData.vboUV != 0) {
            glDeleteBuffers(1, &glData.vboUV);
        }
        // Delete other VBOs like vboNormals, vboUVs, etc., if they were created

        // Delete EBO
        if (glData.ebo != 0) {
            glDeleteBuffers(1, &glData.ebo);
        }
    }
}
unsigned int loadTexture2(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        // 设置纹理的格式
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // 设置纹理参数
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

MeshOpenGLData setupMesh3_3(const hw3::TriangleMesh &mesh) {
    MeshOpenGLData glData{};
    glGenVertexArrays(1, &glData.vao);
    glBindVertexArray(glData.vao);

    // Setup VBO for vertices
    glGenBuffers(1, &glData.vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, glData.vboVertices);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vector3f), mesh.vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0 , 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &glData.vboColors);
    glBindBuffer(GL_ARRAY_BUFFER, glData.vboColors);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertex_colors.size() * sizeof(Vector3f), mesh.vertex_colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1 , 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);


    if (!mesh.faces.empty()) {
        glGenBuffers(1, &glData.ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glData.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.faces.size() * sizeof(Vector3i), mesh.faces.data(), GL_STATIC_DRAW);
    }
    // Unbind VAO to avoid accidental modifications
    glBindVertexArray(0);

    return glData;
}
/*
MeshOpenGLData setupMesh2(const hw3::TriangleMesh &mesh) {
    MeshOpenGLData glData{};
    glGenVertexArrays(1, &glData.vao);
    glBindVertexArray(glData.vao);

    // Setup VBO for vertices
    glGenBuffers(1, &glData.vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, glData.vboVertices);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vector3f), mesh.vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0 , 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &glData.vboColors);
    glBindBuffer(GL_ARRAY_BUFFER, glData.vboColors);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertex_colors.size() * sizeof(Vector3f), mesh.vertex_colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1 , 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);


    if (!mesh.uvs.empty()) {
        glGenBuffers(1, &glData.vboUV);
        glBindBuffer(GL_ARRAY_BUFFER, glData.vboUV);
        glBufferData(GL_ARRAY_BUFFER, mesh.uvs.size() * sizeof(Vector2f), mesh.uvs.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2 , 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(2);
    }

    if (!mesh.faces.empty()) {
        glGenBuffers(1, &glData.ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glData.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.faces.size() * sizeof(Vector3i), mesh.faces.data(), GL_STATIC_DRAW);
    }
    // Unbind VAO to avoid accidental modifications
    glBindVertexArray(0);
    return glData;
}

*/

MeshOpenGLData setupMesh2(const hw3::TriangleMesh &mesh,const std::string& picture_filename) {
    MeshOpenGLData glData{};
    glGenVertexArrays(1, &glData.vao);
    glBindVertexArray(glData.vao);

    // Setup VBO for vertices
    glGenBuffers(1, &glData.vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, glData.vboVertices);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vector3f), mesh.vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0 , 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &glData.vboColors);
    glBindBuffer(GL_ARRAY_BUFFER, glData.vboColors);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertex_colors.size() * sizeof(Vector3f), mesh.vertex_colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);


    if (!mesh.uvs.empty()) {
        glGenBuffers(1, &glData.vboUV);
        glBindBuffer(GL_ARRAY_BUFFER, glData.vboUV);
        glBufferData(GL_ARRAY_BUFFER, mesh.uvs.size() * sizeof(Vector2f), mesh.uvs.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2 , 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(2);
    }


    if (!mesh.faces.empty()) {
        glGenBuffers(1, &glData.ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glData.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.faces.size() * sizeof(Vector3i), mesh.faces.data(), GL_STATIC_DRAW);
    }

    // Load and create a texture
    glGenTextures(1, &glData.textureID);
    glBindTexture(GL_TEXTURE_2D, glData.textureID);
    // Set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load and generate the texture
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(picture_filename.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glBindVertexArray(0);
    return glData;
}


void renderMesh2(const MeshOpenGLData& glData,unsigned int shaderProgram,  const hw3::TriangleMesh& mesh) {
    // Bind the mesh's VAO

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, glData.textureID);
    glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);

    glm::mat4 modelMatrix;
    std::memcpy(&modelMatrix, mesh.model_matrix.ptr(), sizeof(glm::mat4));
    setShaderMatrix(shaderProgram,"model", modelMatrix);

    glBindVertexArray(glData.vao);
    glDrawElements(GL_TRIANGLES, mesh.faces.size() * 3, GL_UNSIGNED_INT, 0);
    // Unbind the VAO and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/*

void renderMesh2(const MeshOpenGLData& glData,unsigned int shaderProgram,  const hw3::TriangleMesh& mesh,const std::string& filename) {
    // Bind the mesh's VAO

    glBindVertexArray(glData.vao);

    glm::mat4 modelMatrix;
    std::memcpy(&modelMatrix, mesh.model_matrix.ptr(), sizeof(glm::mat4));
    setShaderMatrix(shaderProgram,"model", modelMatrix);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, loadTexture(filename.c_str()));

    // Set the texture uniform in your shader, assuming it's named "textureSampler"
    glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);


    glDrawElements(GL_TRIANGLES, mesh.faces.size() * 3, GL_UNSIGNED_INT, 0);
    // Unbind the VAO and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

*/
void renderMesh(const MeshOpenGLData& glData,unsigned int shaderProgram,  const hw3::TriangleMesh& mesh) {
    // Bind the mesh's VAO

    glBindVertexArray(glData.vao);

    glm::mat4 modelMatrix;
    std::memcpy(&modelMatrix, mesh.model_matrix.ptr(), sizeof(glm::mat4));
    setShaderMatrix(shaderProgram,"model", modelMatrix);

    glDrawElements(GL_TRIANGLES, mesh.faces.size() * 3, GL_UNSIGNED_INT, 0);
    // Unbind the VAO and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void hw_3_1(const std::vector<std::string> &params) {
    // 初始化 GLFW
    glfwInit();

    // 设置 GLFW 使用的 OpenGL 版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建一个窗口对象
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    // 初始化 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // 设置视口
    glViewport(0, 0, 600, 480);

    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 输入处理
        processInput(window);

        // 渲染指令
        glClearColor(0.2f, 0.5f, 0.5f, 1.0f); // 设置背景颜色
        glClear(GL_COLOR_BUFFER_BIT);

        // 交换缓冲并轮询IO事件（按键按下/释放、鼠标移动等）
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}


const char* vertexShaderSource3_2 = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float rotationAngle;
uniform float aspectRatio;
out vec3 ourColor;

void main() {
    mat3 aspectRatioScale = mat3(1.0/aspectRatio, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
    float s = sin(rotationAngle);
    float c = cos(rotationAngle);
    mat3 rotationMatrix = mat3(c, -s, 0,
                               s, c, 0,
                               0, 0, 1);
    gl_Position = vec4(rotationMatrix * (aspectRatioScale * aPos), 1.0);
    ourColor = aColor;
}
)glsl";

// 片段着色器代码
const char* fragmentShaderSource3_2 = R"glsl(
#version 330 core
out vec4 FragColor;
in vec3 ourColor;

void main() {
    FragColor = vec4(ourColor, 1.0);
}
)glsl";

const char* vertexShaderSource3_3_texture = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;    // 顶点位置
layout (location = 1) in vec3 aColor;  // 顶点颜色
layout (location = 2) in vec2 aTexCoord; // 纹理坐标

out vec2 TexCoord;

//uniform mat4 u_MVP;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;

void main() {
    ourColor = aColor;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)glsl";

const char* fragmentShaderSource3_3_texture = R"glsl(
#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;
uniform sampler2D ourTexture;

void main() {
    FragColor = texture(ourTexture, TexCoord);
}
)glsl";



const char* vertexShaderSource3 = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;    // 顶点位置
layout (location = 1) in vec3 aColor;  // 顶点颜色

out vec2 TexCoord;

//uniform mat4 u_MVP;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;

void main() {
    ourColor = aColor;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)glsl";


const char* fragmentShaderSource3 = R"glsl(
#version 330 core
out vec4 FragColor;
in vec3 ourColor;

void main() {
    FragColor = vec4(ourColor, 1.0);
}
)glsl";

void rotateCamera(GLFWwindow* window, Vector3 &direction, float xoffset, float yoffset, float& yaw, float& pitch) {
    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // 限制俯仰角范围
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;


    // Update camera direction
    Vector3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction = normalize(front);
}

// 全局变量
float lastX = 400, lastY = 300; // 假设窗口尺寸为 800x600
float yaw = -90.0f;  // 初始化偏航角
float pitch = 0.0f;  // 初始化俯仰角
bool firstMouse = true;
Vector3 cameraDirection;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // 注意这里的y坐标是反的
    lastX = xpos;
    lastY = ypos;

    rotateCamera(window, cameraDirection, xoffset, yoffset, yaw, pitch);
}


void hw_3_3(const std::vector<std::string> &params) {
    if (params.size() == 0) {
        return;
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;
    float lastFrame = 0.0f; // 初始值设为0

    GLFWwindow* window=initOpenGL();
    // 设置视口
    glViewport(0, 0, scene.camera.resolution.x, scene.camera.resolution.y);
    // 设置顶点数据和缓冲，并配置顶点属性
    std::vector<MeshOpenGLData> meshData;
    for (const auto& mesh : scene.meshes) {
        meshData.push_back(setupMesh3_3(mesh));
    }

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource3);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource3);
    unsigned int shaderProgram = linkShaderProgram(vertexShader, fragmentShader);


    glm::mat4 projectionMatrix = glm::mat4(0.0f);
    projectionMatrix[0][0] = 1.0f / (((float)scene.camera.resolution.x / (float)scene.camera.resolution.y) * scene.camera.s);
    projectionMatrix[1][1] = 1.0f / scene.camera.s;
    projectionMatrix[2][2] = -(scene.camera.z_far) / (scene.camera.z_far - scene.camera.z_near);
    projectionMatrix[3][2] = -(scene.camera.z_far * scene.camera.z_near) / (scene.camera.z_far - scene.camera.z_near);
    projectionMatrix[2][3] = -1.0f;
    setShaderMatrix(shaderProgram,"projection",projectionMatrix);

    Matrix4x4f camera_to_world=scene.camera.cam_to_world;
    Vector3 up = Vector3(camera_to_world(0, 1), camera_to_world(1, 1), camera_to_world(2, 1));
    Vector3 right = Vector3(camera_to_world(0, 0), camera_to_world(1, 0), camera_to_world(2, 0));
    Vector3 direction = Vector3(-camera_to_world(0, 2), -camera_to_world(1, 2), -camera_to_world(2, 2));
    cameraDirection=direction;
    Vector3 position = Vector3(camera_to_world(0, 3), camera_to_world(1, 3), camera_to_world(2, 3));

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FRAMEBUFFER_SRGB);


    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;

        processInput2(window,position,direction,up,right,deltaTime);

        camera_to_world(0, 3) = position.x;
        camera_to_world(1, 3) = position.y;
        camera_to_world(2, 3) = position.z;
        camera_to_world(3, 3) = 1;

        /*
         * camera_mouse
        glfwSetCursorPosCallback(window, mouse_callback);
        // 根据新的方向更新camera_to_world矩阵
        Vector3 newFront = normalize(cameraDirection); // 确保方向向量是单位向量
        Vector3 newRight = normalize(cross(newFront, up)); // 重新计算右向量
        Vector3 newUp = cross(newRight, newFront); // 重新计算上向量


        camera_to_world(0, 0) = newRight.x;
        camera_to_world(1, 0) = newRight.y;
        camera_to_world(2, 0) = newRight.z;
        camera_to_world(3, 0) = 0;

        camera_to_world(0, 1) = newUp.x;
        camera_to_world(1, 1) = newUp.y;
        camera_to_world(2, 1) = newUp.z;
        camera_to_world(3, 1) = 0;

        camera_to_world(0, 2) = -newFront.x;
        camera_to_world(1, 2) = -newFront.y;
        camera_to_world(2, 2) = -newFront.z;
        camera_to_world(3, 2) = 0;

         */

        glm::mat4 viewMatrix ; // Assuming you have a conversion function
        std::memcpy(&viewMatrix, (inverse(camera_to_world)).ptr(), sizeof(glm::mat4));
        setShaderMatrix(shaderProgram,"view",viewMatrix);

        // 渲染指令
        glClearColor(scene.background.x,scene.background.y,scene.background.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 使用着色器程序
        glUseProgram(shaderProgram);
        for (size_t i = 0; i < scene.meshes.size(); ++i) {
            renderMesh(meshData[i], shaderProgram, scene.meshes[i]);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cleanup(meshData); // Function to delete OpenGL objects
    glDeleteProgram(shaderProgram);
    glfwTerminate();

}


/*
//  ！！！texture
void hw_3_3(const std::vector<std::string> &params) {

    if (params.size() == 0) {
        return;
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;

    fs::path filepath = params[0];
    std::string filename = filepath.filename().string();
    std::cout<<filename<<std::endl;

    // Determine the texture path based on the filename
    std::string texturePath;
    if (filename == "bunny.json") {
        texturePath = "/Users/shanjiang/balboa_public/scenes/hw3/bunnystanford_res1_UVmapping3072_TerraCotta_g001c.jpg";
    } else if (filename == "teapot.json") {
        texturePath = "/Users/shanjiang/balboa_public/scenes/hw3/teapot.png";
    }else if (filename == "buddha.json") {
        texturePath = "/Users/shanjiang/balboa_public/scenes/hw3/buddha-atlas.jpg";
    }else if (filename == "spheres.json") {
        texturePath = "/Users/shanjiang/balboa_public/scenes/hw3/spheres.jpg";
    }

    float lastFrame = 0.0f; // 初始值设为0

    GLFWwindow* window=initOpenGL();
    // 设置视口
    glViewport(0, 0, scene.camera.resolution.x, scene.camera.resolution.y);
    // 设置顶点数据和缓冲，并配置顶点属性
    std::vector<MeshOpenGLData> meshData;
    for (const auto& mesh : scene.meshes) {
        meshData.push_back(setupMesh2(mesh,texturePath));
    }

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource3_3_texture);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource3_3_texture);
    unsigned int shaderProgram = linkShaderProgram(vertexShader, fragmentShader);


    glm::mat4 projectionMatrix = glm::mat4(0.0f);
    projectionMatrix[0][0] = 1.0f / (((float)scene.camera.resolution.x / (float)scene.camera.resolution.y) * scene.camera.s);
    projectionMatrix[1][1] = 1.0f / scene.camera.s;
    projectionMatrix[2][2] = -(scene.camera.z_far) / (scene.camera.z_far - scene.camera.z_near);
    projectionMatrix[3][2] = -(scene.camera.z_far * scene.camera.z_near) / (scene.camera.z_far - scene.camera.z_near);
    projectionMatrix[2][3] = -1.0f;
    setShaderMatrix(shaderProgram,"projection",projectionMatrix);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FRAMEBUFFER_SRGB);


    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glm::mat4 viewMatrix ; // Assuming you have a conversion function
        std::memcpy(&viewMatrix, (inverse(scene.camera.cam_to_world)).ptr(), sizeof(glm::mat4));
        setShaderMatrix(shaderProgram,"view",viewMatrix);

        // 渲染指令
        glClearColor(scene.background.x,scene.background.y,scene.background.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 使用着色器程序
        glUseProgram(shaderProgram);
        for (size_t i = 0; i < scene.meshes.size(); ++i) {
            renderMesh2(meshData[i], shaderProgram, scene.meshes[i]);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cleanup(meshData); // Function to delete OpenGL objects
    glDeleteProgram(shaderProgram);
    glfwTerminate();

}
*/

const char* vertexShaderSource2 = R"glsl(
#version 330 core
out vec4 vertexColor; // Specify a color output to the fragment shader

void main() {
    // Define the positions of the triangle's vertices
    vec2 positions[3] = vec2[](vec2(-0.5, -0.5), vec2(0.5, -0.5), vec2(0.0, 0.5));

    // Hardcoded color for each vertex
    vec3 colors[3] = vec3[](vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0));

    // Set the position and color for each vertex
    gl_Position = vec4(positions[gl_VertexID], 0.0, 1.0);
    vertexColor = vec4(colors[gl_VertexID], 1.0);
}

)glsl";


// 片段着色器代码
const char* fragmentShaderSource2 = R"glsl(
#version 330 core
in vec4 vertexColor; // Input color from the vertex shader
out vec4 FragColor;

void main() {
    // Set the color of each fragment to the color passed from the vertex shader
    FragColor = vertexColor;
}
)glsl";


void hw_3_2(const std::vector<std::string> &params) {

    GLFWwindow* window=initOpenGL();
    // 设置视口
    glViewport(0, 0, 800, 600);
    // 设置顶点数据和缓冲，并配置顶点属性
    float vertices[] = {
            0.5f, -0.5f, 0.0f,  0.5f, 0.8f, 0.5f,   // bottom right
            -0.5f, -0.5f, 0.0f,  0.5f, 0.8f, 0.5f,   // bottom left
            0.0f,  0.5f, 0.0f,  0.5f, 0.5f, 0.8f    // top
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource3_2);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource3_2);
    unsigned int shaderProgram = linkShaderProgram(vertexShader, fragmentShader);

    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // 渲染指令
        glClearColor(0.2f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 使用着色器程序
        glUseProgram(shaderProgram);
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float aspectRatio = (float)width / (float)height;
        int aspectRatioLocation = glGetUniformLocation(shaderProgram, "aspectRatio");
        glUniform1f(aspectRatioLocation, aspectRatio);


        if (isRotating) {
            float timeValue = glfwGetTime();
            float rotationAngle = timeValue; // 或者使用其他函数来计算旋转角度，比如：sin(timeValue)

            int rotationLocation = glGetUniformLocation(shaderProgram, "rotationAngle");
            glUniform1f(rotationLocation, rotationAngle);

        }

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
}


glm::mat4 convertToGLMMatrix(const TMatrix4x4<float>& matrix) {
    glm::mat4 glmMatrix;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            glmMatrix[i][j] = matrix(i, j);
        }
    }
    return glmMatrix;
}

MeshOpenGLData setupMesh_4(const hw3::TriangleMesh &mesh) {
    MeshOpenGLData glData{};
    glGenVertexArrays(1, &glData.vao);
    glBindVertexArray(glData.vao);

    // Setup VBO for vertices
    glGenBuffers(1, &glData.vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, glData.vboVertices);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vector3f), mesh.vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0 , 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &glData.vboColors);
    glBindBuffer(GL_ARRAY_BUFFER, glData.vboColors);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertex_colors.size() * sizeof(Vector3f), mesh.vertex_colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1 , 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    if (!mesh.vertex_normals.empty()) {
        glGenBuffers(1, &glData.vboNormals);
        glBindBuffer(GL_ARRAY_BUFFER, glData.vboNormals);
        glBufferData(GL_ARRAY_BUFFER, mesh.vertex_normals.size() * sizeof(Vector3f), mesh.vertex_normals.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2 , 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(2);
    }

    if (!mesh.faces.empty()) {
        glGenBuffers(1, &glData.ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glData.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.faces.size() * sizeof(Vector3i), mesh.faces.data(), GL_STATIC_DRAW);
    }
    // Unbind VAO to avoid accidental modifications
    glBindVertexArray(0);

    return glData;
}









const char* vertexShaderSource4 = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;
out vec3 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    Color = aColor; // Pass the vertex color to the fragment shader

    gl_Position = projection * view * vec4(FragPos, 1.0);
}


)glsl";


// 片段着色器代码
const char* fragmentShaderSource4 = R"glsl(
#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 Color;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float ambientStrength;
uniform float specularStrength;
uniform vec3 lightColor;

void main()
{
    // Ambient
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * Color;
    FragColor = vec4(result, 1.0);
}

)glsl";


void hw_3_4(const std::vector<std::string> &params) {
    if (params.size() == 0) {
        return;
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;
    float lastFrame = 0.0f; // 初始值设为0

    GLFWwindow* window=initOpenGL();
    // 设置视口
    glViewport(0, 0, scene.camera.resolution.x, scene.camera.resolution.y);
    // 设置顶点数据和缓冲，并配置顶点属性
    std::vector<MeshOpenGLData> meshData;
    for (const auto& mesh : scene.meshes) {
        meshData.push_back(setupMesh_4(mesh));
    }

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource4);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource4);
    unsigned int shaderProgram = linkShaderProgram(vertexShader, fragmentShader);


    glm::mat4 projectionMatrix = glm::mat4(0.0f);
    projectionMatrix[0][0] = 1.0f / (((float)scene.camera.resolution.x / (float)scene.camera.resolution.y) * scene.camera.s);
    projectionMatrix[1][1] = 1.0f / scene.camera.s;
    projectionMatrix[2][2] = -(scene.camera.z_far) / (scene.camera.z_far - scene.camera.z_near);
    projectionMatrix[3][2] = -(scene.camera.z_far * scene.camera.z_near) / (scene.camera.z_far - scene.camera.z_near);
    projectionMatrix[2][3] = -1.0f;
    setShaderMatrix(shaderProgram,"projection",projectionMatrix);


    Matrix4x4f camera_to_world=scene.camera.cam_to_world;
    Vector3 up = Vector3(camera_to_world(0, 1), camera_to_world(1, 1), camera_to_world(2, 1));
    Vector3 right = Vector3(camera_to_world(0, 0), camera_to_world(1, 0), camera_to_world(2, 0));
    Vector3 direction = Vector3(-camera_to_world(0, 2), -camera_to_world(1, 2), -camera_to_world(2, 2));
    cameraDirection=direction;
    Vector3 position = Vector3(camera_to_world(0, 3), camera_to_world(1, 3), camera_to_world(2, 3));


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FRAMEBUFFER_SRGB);

    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(shaderProgram, "viewPos"), position.x, position.y, position.z);
        glUniform1f(glGetUniformLocation(shaderProgram, "ambientStrength"), 0.1f);
        glUniform1f(glGetUniformLocation(shaderProgram, "specularStrength"), 0.5f);
        glUniform3f(glGetUniformLocation(shaderProgram, "lightColor"), 1.0f, 1.0f, 1.0f);

        glm::mat4 viewMatrix ; // Assuming you have a conversion function
        std::memcpy(&viewMatrix, (inverse(scene.camera.cam_to_world)).ptr(), sizeof(glm::mat4));
        setShaderMatrix(shaderProgram,"view",viewMatrix);

        // 渲染指令
        glClearColor(scene.background.x,scene.background.y,scene.background.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 使用着色器程序
        glUseProgram(shaderProgram);
        for (size_t i = 0; i < scene.meshes.size(); ++i) {
            renderMesh(meshData[i], shaderProgram, scene.meshes[i]);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cleanup(meshData); // Function to delete OpenGL objects
    glDeleteProgram(shaderProgram);
    glfwTerminate();

}


/*
 * with animation

void hw_3_4(const std::vector<std::string> &params) {
    // HW 3.4: Render a scene with lighting
    if (params.size() == 0) {
        return;
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;
    float lastFrame = 0.0f; // 初始值设为0

    GLFWwindow* window=initOpenGL();
    // 设置视口
    glViewport(0, 0, scene.camera.resolution.x, scene.camera.resolution.y);
    // 设置顶点数据和缓冲，并配置顶点属性
    std::vector<MeshOpenGLData> meshData;
    for (const auto& mesh : scene.meshes) {
        meshData.push_back(setupMesh_4(mesh));
    }

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource4);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource4);
    unsigned int shaderProgram = linkShaderProgram(vertexShader, fragmentShader);


    glm::mat4 projectionMatrix = glm::mat4(0.0f);
    projectionMatrix[0][0] = 1.0f / (((float)scene.camera.resolution.x / (float)scene.camera.resolution.y) * scene.camera.s);
    projectionMatrix[1][1] = 1.0f / scene.camera.s;
    projectionMatrix[2][2] = -(scene.camera.z_far) / (scene.camera.z_far - scene.camera.z_near);
    projectionMatrix[3][2] = -(scene.camera.z_far * scene.camera.z_near) / (scene.camera.z_far - scene.camera.z_near);
    projectionMatrix[2][3] = -1.0f;
    setShaderMatrix(shaderProgram,"projection",projectionMatrix);

    Matrix4x4f camera_to_world=scene.camera.cam_to_world;
    Vector3 up = Vector3(camera_to_world(0, 1), camera_to_world(1, 1), camera_to_world(2, 1));
    Vector3 right = Vector3(camera_to_world(0, 0), camera_to_world(1, 0), camera_to_world(2, 0));
    Vector3 direction = Vector3(-camera_to_world(0, 2), -camera_to_world(1, 2), -camera_to_world(2, 2));
    cameraDirection=direction;
    Vector3 position = Vector3(camera_to_world(0, 3), camera_to_world(1, 3), camera_to_world(2, 3));



    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FRAMEBUFFER_SRGB);


    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;

        processInput2(window,position,direction,up,right,deltaTime);

        camera_to_world(0, 3) = position.x;
        camera_to_world(1, 3) = position.y;
        camera_to_world(2, 3) = position.z;
        camera_to_world(3, 3) = 1;

        float timeValue = glfwGetTime();
        float lightX = sin(timeValue) * 2.0; // radius是光源绕圈的半径
        float lightY = 1.0; // height是光源的高度
        float lightZ = cos(timeValue) * 2.0;
        glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);

        glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

        float redValue = sin(timeValue) / 4.0f + 0.75f;
        float greenValue = cos(timeValue) / 4.0f + 0.75f;
        glm::vec3 lightColor = glm::vec3(redValue, greenValue, 1.0f);

        glUniform3f(glGetUniformLocation(shaderProgram, "lightColor"), lightColor.x, lightColor.y, lightColor.z);


        // glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(shaderProgram, "viewPos"), position.x, position.y, position.z);
        glUniform1f(glGetUniformLocation(shaderProgram, "ambientStrength"), 0.1f);
        glUniform1f(glGetUniformLocation(shaderProgram, "specularStrength"), 0.5f);
        //glUniform3f(glGetUniformLocation(shaderProgram, "lightColor"), 1.0f, 1.0f, 1.0f);


        glm::mat4 viewMatrix ; // Assuming you have a conversion function
        std::memcpy(&viewMatrix, (inverse(camera_to_world)).ptr(), sizeof(glm::mat4));
        setShaderMatrix(shaderProgram,"view",viewMatrix);

        // 渲染指令
        glClearColor(scene.background.x,scene.background.y,scene.background.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 使用着色器程序
        glUseProgram(shaderProgram);
        for (size_t i = 0; i < scene.meshes.size(); ++i) {
            renderMesh(meshData[i], shaderProgram, scene.meshes[i]);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cleanup(meshData); // Function to delete OpenGL objects
    glDeleteProgram(shaderProgram);
    glfwTerminate();

}
*/


const char* fragmentShaderSource5 = R"glsl(
#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 Color;

// Directional light
uniform vec3 lightPos;
uniform vec3 lightColor;

// Point light
struct PointLight {
    vec3 position;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};
uniform PointLight pointLight;

// Spot light
struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 color;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
};
uniform SpotLight spotLight;

uniform vec3 viewPos;
uniform float ambientStrength;
uniform float specularStrength;

// Utility function to calculate lighting
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Ambient component (common for all lights)
    vec3 ambient = ambientStrength * lightColor;

    // Directional light calculations
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // Point light calculations
    vec3 pointLightResult = CalcPointLight(pointLight, norm, FragPos);

    // Spot light calculations
    vec3 spotLightResult = CalcSpotLight(spotLight, norm, FragPos);

    vec3 result = (ambient + diffuse + specular + pointLightResult + spotLightResult) * Color;
    FragColor = vec4(result, 1.0);
}

// Function for calculating point light contribution
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos) {
    vec3 lightDir = normalize(light.position - fragPos);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * light.color;

    return (diffuse + specular) * attenuation;
}

// Function for calculating spot light contribution
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos) {
    vec3 lightDir = normalize(light.position - fragPos);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * light.color;

    return (diffuse + specular) * attenuation * intensity;
}

)glsl";

/*
 * different type of lights
 */
/*
void hw_3_4(const std::vector<std::string> &params) {
    // HW 3.4: Render a scene with lighting
    if (params.size() == 0) {
        return;
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;
    float lastFrame = 0.0f; // 初始值设为0

    GLFWwindow* window=initOpenGL();
    // 设置视口
    glViewport(0, 0, scene.camera.resolution.x, scene.camera.resolution.y);
    // 设置顶点数据和缓冲，并配置顶点属性
    std::vector<MeshOpenGLData> meshData;
    for (const auto& mesh : scene.meshes) {
        meshData.push_back(setupMesh_4(mesh));
    }

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource4);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource5);
    unsigned int shaderProgram = linkShaderProgram(vertexShader, fragmentShader);


    glm::mat4 projectionMatrix = glm::mat4(0.0f);
    projectionMatrix[0][0] = 1.0f / (((float)scene.camera.resolution.x / (float)scene.camera.resolution.y) * scene.camera.s);
    projectionMatrix[1][1] = 1.0f / scene.camera.s;
    projectionMatrix[2][2] = -(scene.camera.z_far) / (scene.camera.z_far - scene.camera.z_near);
    projectionMatrix[3][2] = -(scene.camera.z_far * scene.camera.z_near) / (scene.camera.z_far - scene.camera.z_near);
    projectionMatrix[2][3] = -1.0f;
    setShaderMatrix(shaderProgram,"projection",projectionMatrix);

    Matrix4x4f camera_to_world=scene.camera.cam_to_world;
    Vector3 up = Vector3(camera_to_world(0, 1), camera_to_world(1, 1), camera_to_world(2, 1));
    Vector3 right = Vector3(camera_to_world(0, 0), camera_to_world(1, 0), camera_to_world(2, 0));
    Vector3 direction = Vector3(-camera_to_world(0, 2), -camera_to_world(1, 2), -camera_to_world(2, 2));
    cameraDirection=direction;
    Vector3 position = Vector3(camera_to_world(0, 3), camera_to_world(1, 3), camera_to_world(2, 3));



    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FRAMEBUFFER_SRGB);


    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;

        processInput2(window,position,direction,up,right,deltaTime);

        camera_to_world(0, 3) = position.x;
        camera_to_world(1, 3) = position.y;
        camera_to_world(2, 3) = position.z;
        camera_to_world(3, 3) = 1;


        // 点光源设置
        glm::vec3 pointLightPos = glm::vec3(-5.0f, 0.0f, 0.0f);  // 例如，X = 10, Y = 0, Z = 0
        glUniform3f(glGetUniformLocation(shaderProgram, "pointLight.position"), pointLightPos.x, pointLightPos.y, pointLightPos.z);
        glUniform3f(glGetUniformLocation(shaderProgram, "pointLight.color"), 0.0, 0.0, 1.0);
        glUniform1f(glGetUniformLocation(shaderProgram, "pointLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(shaderProgram, "pointLight.linear"), 0.09f);
        glUniform1f(glGetUniformLocation(shaderProgram, "pointLight.quadratic"), 0.032f);

// 聚光灯设置
        glm::vec3 spotLightPos = glm::vec3(5.0f, 0.0f, 0.0f);  // 例如，X = 10, Y = 0, Z = 0

// 聚光灯方向朝向画面左侧
        glm::vec3 spotLightDir = glm::vec3(-1.0f, 0.0f, 0.0f);  // 朝向负X方向
        glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.position"), spotLightPos.x, spotLightPos.y, spotLightPos.z);
        glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.direction"), spotLightDir.x, spotLightDir.y, spotLightDir.z);
        glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.color"), 0.0, 1.0, 0.0);
        glUniform1f(glGetUniformLocation(shaderProgram, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
        glUniform1f(glGetUniformLocation(shaderProgram, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));
        glUniform1f(glGetUniformLocation(shaderProgram, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(shaderProgram, "spotLight.linear"), 0.09f);
        glUniform1f(glGetUniformLocation(shaderProgram, "spotLight.quadratic"), 0.032f);

// 更新现有的统一变量
        glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(shaderProgram, "viewPos"), position.x, position.y, position.z);
        glUniform1f(glGetUniformLocation(shaderProgram, "ambientStrength"), 0.1f);
        glUniform1f(glGetUniformLocation(shaderProgram, "specularStrength"), 0.5f);
        glUniform3f(glGetUniformLocation(shaderProgram, "lightColor"), 1.0f, 1.0f, 1.0f); // 可以是定向光的颜色


        glm::mat4 viewMatrix ; // Assuming you have a conversion function
        std::memcpy(&viewMatrix, (inverse(camera_to_world)).ptr(), sizeof(glm::mat4));
        setShaderMatrix(shaderProgram,"view",viewMatrix);

        // 渲染指令
        glClearColor(scene.background.x,scene.background.y,scene.background.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 使用着色器程序
        glUseProgram(shaderProgram);
        for (size_t i = 0; i < scene.meshes.size(); ++i) {
            renderMesh(meshData[i], shaderProgram, scene.meshes[i]);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cleanup(meshData); // Function to delete OpenGL objects
    glDeleteProgram(shaderProgram);
    glfwTerminate();

}
*/