#include "hw2.h"
#include "hw2_scenes.h"
#include <vector>
#include <cmath>

using namespace hw2;

static bool IsPointInsideTriangle( Vector2 point,  Vector2 p0,  Vector2 p1, Vector2 p2) {
    Vector2 edge0 = p1 - p0;
    Vector2 edge1 = p2 - p1;
    Vector2 edge2 = p0 - p2;

    Vector2 point0 = point - p0;
    Vector2 point1 = point - p1;
    Vector2 point2 = point - p2;

    double dot0 = edge0.x * point0.y - edge0.y * point0.x;
    double dot1 = edge1.x * point1.y - edge1.y * point1.x;
    double dot2 = edge2.x * point2.y - edge2.y * point2.x;

    return (dot0 >= 0 && dot1 >= 0 && dot2 >= 0) || (dot0 <= 0 && dot1 <= 0 && dot2 <= 0) ;
}

struct Triangle2 {
    Vector2 vertices[3];
    Vector3 color;
    Vector3 verticesColor[3];

};
struct Triangle3 {
    Vector3 vertices[3];
    Vector3 color;
    Vector3 verticesColor[3];
    Real z_near{};
};
std::vector<Triangle3> ClipTriangleAgainstNearPlane(const Triangle3& inputTriangle) {
    std::vector<Triangle3> clippedTriangles;
    std::vector<Vector3> insideVertices;
    std::vector<Vector3> outsideVertices;

    for (int i = 0; i < 3; i++) {
        if (inputTriangle.vertices[i].z >= inputTriangle.z_near) {
            outsideVertices.push_back(inputTriangle.vertices[i]);
        } else {
            insideVertices.push_back(inputTriangle.vertices[i]);
        }
    }

    if (insideVertices.size() == 3) {
        clippedTriangles.push_back(inputTriangle);
    }else if (insideVertices.size() == 2) {
        Vector3 intersection1 = insideVertices[0] + (inputTriangle.z_near - insideVertices[0].z) *
                                                    (outsideVertices[0] - insideVertices[0]) / (outsideVertices[0].z - insideVertices[0].z);
        Vector3 intersection2 = insideVertices[1] + (inputTriangle.z_near - insideVertices[1].z) *
                                                    (outsideVertices[0] - insideVertices[1]) / (outsideVertices[0].z - insideVertices[1].z);
        Triangle3 newTriangle1;
        newTriangle1.vertices[0] = insideVertices[0];
        newTriangle1.vertices[1] = insideVertices[1];
        newTriangle1.vertices[2] = intersection1;
        std::cout<< newTriangle1.vertices[0]<<newTriangle1.vertices[1]<<newTriangle1.vertices[2]<<std::endl;
        newTriangle1.color = inputTriangle.color;
        newTriangle1.z_near = inputTriangle.z_near;
        clippedTriangles.push_back(newTriangle1);

        Triangle3 newTriangle2;
        newTriangle2.vertices[0] = insideVertices[1];
        newTriangle2.vertices[1] = intersection1;
        newTriangle2.vertices[2] = intersection2;
        std::cout<< newTriangle2.vertices[0]<<newTriangle2.vertices[1]<<newTriangle2.vertices[2]<<std::endl;
        newTriangle2.color = inputTriangle.color;
        newTriangle2.z_near = inputTriangle.z_near;
        clippedTriangles.push_back(newTriangle2);
    } else if (insideVertices.size() == 1) {
        Vector3 intersection1 = insideVertices[0] + (inputTriangle.z_near - insideVertices[0].z) *
                                                    (outsideVertices[0] - insideVertices[0]) / (outsideVertices[0].z - insideVertices[0].z);
        Vector3 intersection2 = insideVertices[0] + (inputTriangle.z_near - insideVertices[0].z) *
                                                    (outsideVertices[1] - insideVertices[0]) / (outsideVertices[1].z - insideVertices[0].z);
        Triangle3 newTriangle;
        newTriangle.vertices[0] = insideVertices[0];
        std::cout<< newTriangle.vertices[0]<<std::endl;
        newTriangle.vertices[1] = intersection1;
        std::cout<< newTriangle.vertices[1]<<std::endl;
        newTriangle.vertices[2] = intersection2;
        std::cout<< newTriangle.vertices[2]<<std::endl;
        newTriangle.color = inputTriangle.color;
        newTriangle.z_near = inputTriangle.z_near;
        clippedTriangles.push_back(newTriangle);
    }
    return clippedTriangles;
}

Image3 hw_2_1(const std::vector<std::string> &params) {
    // Homework 2.1: render a single 3D triangle

    Image3 img(640 /* width */, 480 /* height */);

    Vector3 p0{0, 0, -1};
    Vector3 p1{1, 0, -1};
    Vector3 p2{0, 1, -1};
    Real s = 1; // scaling factor of the view frustrum
    Vector3 color = Vector3{1.0, 0.5, 0.5};
    Real z_near = 1e-6; // distance of the near clipping plane
    Real a = static_cast<Real>(img.width) / img.height;

    Triangle3 tra;
    std::vector<Triangle3> triangleCollection;

    for (int i = 0; i < (int)params.size(); i++) {
        if (params[i] == "-s") {
            s = std::stof(params[++i]);
        } else if (params[i] == "-p0") {
            p0.x = std::stof(params[++i]);
            p0.y = std::stof(params[++i]);
            p0.z = std::stof(params[++i]);
        } else if (params[i] == "-p1") {
            p1.x = std::stof(params[++i]);
            p1.y = std::stof(params[++i]);
            p1.z = std::stof(params[++i]);
        } else if (params[i] == "-p2") {
            p2.x = std::stof(params[++i]);
            p2.y = std::stof(params[++i]);
            p2.z = std::stof(params[++i]);
        } else if (params[i] == "-color") {
            Real r = std::stof(params[++i]);
            Real g = std::stof(params[++i]);
            Real b = std::stof(params[++i]);
            color = Vector3{r, g, b};
        } else if (params[i] == "-znear") {
            z_near = std::stof(params[++i]);
        }
        tra.vertices[0]=p0;
        tra.vertices[1]=p1;
        tra.vertices[2]=p2;
        tra.color=color;
        tra.z_near=z_near;
    }

    triangleCollection= ClipTriangleAgainstNearPlane(tra);
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            img(x, y) = Vector3{0.5, 0.5, 0.5};
        }
    }

    Vector2 pix;

    for (const Triangle3& triangle3 : triangleCollection) {

        Triangle2 tri;
        Vector2 cameraSpace_p0{0, 1};
        Vector2 cameraSpace_p1{0, 1};
        Vector2 cameraSpace_p2{0, 1};
        Vector2 imageSpace_p0{0, 1};
        Vector2 imageSpace_p1{0, 1};
        Vector2 imageSpace_p2{0, 1};
        cameraSpace_p0.x=triangle3.vertices[0].x/( - triangle3.vertices[0].z);
        cameraSpace_p0.y=triangle3.vertices[0].y/( - triangle3.vertices[0].z);
        cameraSpace_p1.x=triangle3.vertices[1].x/(- triangle3.vertices[1].z);
        cameraSpace_p1.y=triangle3.vertices[1].y/( - triangle3.vertices[1].z);
        cameraSpace_p2.x=triangle3.vertices[2].x/( - triangle3.vertices[2].z);
        cameraSpace_p2.y=triangle3.vertices[2].y/( - triangle3.vertices[2].z);

        imageSpace_p0.x=img.width*(cameraSpace_p0.x+a*s)/(2*a*s);
        imageSpace_p1.x=img.width*(cameraSpace_p1.x+a*s)/(2*a*s);
        imageSpace_p2.x=img.width*(cameraSpace_p2.x+a*s)/(2*a*s);
        imageSpace_p0.y=img.height-img.height*(cameraSpace_p0.y+s)/(2*s);
        imageSpace_p1.y=img.height-img.height*(cameraSpace_p1.y+s)/(2*s);
        imageSpace_p2.y=img.height-img.height*(cameraSpace_p2.y+s)/(2*s);
        tri.vertices[0]=imageSpace_p0;
        tri.vertices[1]=imageSpace_p1;
        tri.vertices[2]=imageSpace_p2;
        tri.color=triangle3.color;

        for (int y = 0; y < img.height; y++) {
                for (int x = 0; x < img.width; x++) {
                    Vector3 pixelColor = {0,0,0};
                    bool hit= false;
                    for (int sub_y =0 ; sub_y<4; sub_y++){
                        for (int sub_x=0; sub_x<4; sub_x++){
                            double subPixelX = x + (0.125 + 0.25 * sub_x);
                            double subPixelY = y + (0.125 + 0.25 * sub_y);
                            pix.x=subPixelX;
                            pix.y=subPixelY;
                            if (IsPointInsideTriangle(pix, tri.vertices[0], tri.vertices[1], tri.vertices[2])) {
                                hit= true;
                                pixelColor += tri.color;
                            } else{
                                pixelColor+=img(x,y);
                            }
                        }
                    }
                    if(hit){
                        pixelColor/=16.0;
                        img(x, y) = pixelColor;
                    }
                }
            }
    }

    return img;
}

double calculateTriangleArea(Vector2 p0, Vector2 p1, Vector2 p2) {
    Vector3 s1={(p0-p1).x,(p0-p1).y,0.0};
    Vector3 s2={(p0-p2).x,(p0-p2).y,0.0};
    double area =length(cross(s1,s2))/2.0;
    std::cout<<area<<std::endl;
    return area;
}
double calculateTriangleArea3(Vector3 p0, Vector3 p1, Vector3 p2) {
    Vector3 s1=p0-p1;
    Vector3 s2=p0-p2;
    double area =length(cross(s1,s2))/2.0;
    std::cout<<area<<std::endl;
    return area;
}
double calculateTriangleArea2(Vector2 p0, Vector2 p1, Vector2 p2) {
    Vector2 edge1 = p1 - p0;
    Vector2 edge2 = p2 - p0;
    double crossProduct = edge1.x * edge2.y - edge1.y * edge2.x;
    return 0.5 * std::abs(crossProduct);
}

void calculateProjectedBarycentricCoordinates(Vector2 p, Vector2 p0, Vector2 p1, Vector2 p2, double& b0, double& b1, double& b2) {
    double areaTriangle = calculateTriangleArea2(p0, p1, p2);
    b0 = calculateTriangleArea2(p, p1, p2) / areaTriangle;
    b1 = calculateTriangleArea2(p0, p, p2) / areaTriangle;
    b2 = calculateTriangleArea2(p0, p1, p) / areaTriangle;
}

void calculateOriginalBarycentricCoordinates(Vector3 p0, Vector3 p1, Vector3 p2,double& b0,double& b1, double& b2,double& b_0,double& b_1, double& b_2) {
    double B=1.0/(b_0/p0.z+b_1/p1.z+b_2/p2.z);
    b0 = (b_0/p0.z)*B;
    b1 = (b_1/p1.z)*B;
    b2 = (b_2/p2.z)*B;
}
double calculateDepth(const double& b0, const double& b1, const double& b2, Vector3 p0, Vector3 p1, Vector3 p2) {
    return b0 * p0.z + b1 * p1.z + b2 * p2.z;
}

struct HierarchicalZBuffer {
    std::vector<std::vector<double>> buffer; // 2D array for storing depth values
    int width, height; // Dimensions of the buffer
    int levels; // Number of hierarchy levels

    HierarchicalZBuffer(int w, int h, int numLevels) : width(w), height(h), levels(numLevels) {
        buffer.resize(levels);
        for (int level = 0; level < levels; level++) {
            int levelWidth = width >> level;
            int levelHeight = height >> level;
            buffer[level].resize(levelWidth * levelHeight, std::numeric_limits<double>::max());
        }
    }

    // Update the hierarchical Z-buffer with the depth value at a given pixel position.
    void update(int x, int y, double depth) {
        for (int level = 0; level < levels; level++) {
            int levelX = x >> level;
            int levelY = y >> level;
            buffer[level][levelY * (width >> level) + levelX] = std::min(buffer[level][levelY * (width >> level) + levelX], depth);
        }
    }

    // Check if a pixel is occluded using the hierarchical Z-buffer.
    bool isOccluded(int x, int y, double depth) {
        for (int level = 0; level < levels; level++) {
            int levelX = x >> level;
            int levelY = y >> level;
            if (depth >= buffer[level][levelY * (width >> level) + levelX]) {
                return true; // The pixel is occluded at this level
            }
        }
        return false; // The pixel is visible
    }
};



Image3 hw_2_2(const std::vector<std::string> &params) {
    // Homework 2.2: render a triangle mesh

    Image3 img(640 /* width */, 480 /* height */);

    Real s = 1; // scaling factor of the view frustrum
    Real z_near = 1e-6; // distance of the near clipping plane
    int scene_id = 0;
    for (int i = 0; i < (int)params.size(); i++) {
        if (params[i] == "-s") {
            s = std::stof(params[++i]);
        } else if (params[i] == "-znear") {
            z_near = std::stof(params[++i]);
        } else if (params[i] == "-scene_id") {
            scene_id = std::stoi(params[++i]);
        }
    }



    TriangleMesh mesh = meshes[scene_id];
    std::vector<Triangle3> worldTriangles;
    std::vector<Vector3> worldVertices;

    for (size_t i = 0; i < mesh.faces.size(); i++) {
        const Vector3& face = mesh.faces[i];
        Triangle3 triangle;
        triangle.vertices[0] = mesh.vertices[face.x];
        triangle.vertices[1] = mesh.vertices[face.y];
        triangle.vertices[2] = mesh.vertices[face.z];
        triangle.color = mesh.face_colors[i];

        worldTriangles.push_back(triangle);
    }
    Real a = static_cast<Real>(img.width) / img.height;
    std::vector<Triangle2> projectedTriangles;

    for (const Triangle3& triangle3 : worldTriangles) {
        Triangle2 tri;
        for (int i = 0; i < 3; i++) {
            Vector2 cameraSpacePoint{
                    triangle3.vertices[i].x / (-triangle3.vertices[i].z),
                    triangle3.vertices[i].y / (-triangle3.vertices[i].z)
            };
            Vector2 imageSpacePoint{
                    img.width * (cameraSpacePoint.x + a * s) / (2 * a * s),
                    img.height - img.height * (cameraSpacePoint.y + s) / (2 * s)
            };
            tri.vertices[i] = imageSpacePoint;
        }
        tri.color = triangle3.color;
        projectedTriangles.push_back(tri);
    }
    Vector2 pix;
    Image3 Z_buffer(img.width, img.height);


    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            Vector3 pixelColor = {0,0,0};

            for (int sub_y =0 ; sub_y<4; sub_y++){
                for (int sub_x=0; sub_x<4; sub_x++){
                    Z_buffer(x, y).z = std::numeric_limits<double>::infinity();
                    double subPixelX = x + (0.125 + 0.25 * sub_x);
                    double subPixelY = y + (0.125 + 0.25 * sub_y);
                    pix.x=subPixelX;
                    pix.y=subPixelY;
                    Vector3 color={0.5,0.5,0.5};
                    for (size_t i = 0; i < projectedTriangles.size(); i++){
                        Triangle2 triangle2=projectedTriangles[i];

                        double b_0,b_1,b_2=0;
                        double b0,b1,b2=0;
                        double depth_at_pix;
                        double inverse_depth;
                        if (IsPointInsideTriangle(pix, triangle2.vertices[0], triangle2.vertices[1], triangle2.vertices[2])) {
                            calculateProjectedBarycentricCoordinates(pix,triangle2.vertices[0],triangle2.vertices[1],triangle2.vertices[2],b_0,b_1,b_2);
                            calculateOriginalBarycentricCoordinates(worldTriangles[i].vertices[0],worldTriangles[i].vertices[1],worldTriangles[i].vertices[2],b0,b1,b2,b_0,b_1,b_2);
                            depth_at_pix= calculateDepth(b0,b1,b2,worldTriangles[i].vertices[0],worldTriangles[i].vertices[1],worldTriangles[i].vertices[2]);
                            inverse_depth=-depth_at_pix;

                            if (inverse_depth <= Z_buffer(x, y).z) {
                                Z_buffer(x, y).z = inverse_depth; // 更新深度缓冲
                                color= triangle2.color;
                            }
                        }
                    }
                    pixelColor+=color;
                }
            }
            pixelColor/=16.0;
            img(x, y) = pixelColor;
        }
    }

    return img;
}

Image3 hw_2_3(const std::vector<std::string> &params) {
    // Homework 2.3: render a triangle mesh with vertex colors

    Image3 img(640 /* width */, 480 /* height */);

    Real s = 1; // scaling factor of the view frustrum
    Real z_near = 1e-6; // distance of the near clipping plane
    int scene_id = 0;
    for (int i = 0; i < (int)params.size(); i++) {
        if (params[i] == "-s") {
            s = std::stof(params[++i]);
        } else if (params[i] == "-znear") {
            z_near = std::stof(params[++i]);
        } else if (params[i] == "-scene_id") {
            scene_id = std::stoi(params[++i]);
        }
    }
    Image3 Z_buffer(img.width, img.height);

    TriangleMesh mesh = meshes[scene_id];
    std::vector<Triangle3> worldTriangles;

    for (size_t i = 0; i < mesh.faces.size(); i++) {
        const Vector3& face = mesh.faces[i];
        Triangle3 triangle;
        triangle.vertices[0] = mesh.vertices[face.x];
        triangle.verticesColor[0]=mesh.vertex_colors[face.x];
        triangle.vertices[1] = mesh.vertices[face.y];
        triangle.verticesColor[1]=mesh.vertex_colors[face.y];
        triangle.vertices[2] = mesh.vertices[face.z];
        triangle.verticesColor[2]=mesh.vertex_colors[face.z];
        triangle.color = mesh.face_colors[i];

        worldTriangles.push_back(triangle);
    }
    Real a = static_cast<Real>(img.width) / img.height;
    std::vector<Triangle2> projectedTriangles;

    for (const Triangle3& triangle3 : worldTriangles) {
        Triangle2 tri;
        for (int i = 0; i < 3; i++) {
            Vector2 cameraSpacePoint{
                    triangle3.vertices[i].x / (-triangle3.vertices[i].z),
                    triangle3.vertices[i].y / (-triangle3.vertices[i].z)
            };
            Vector2 imageSpacePoint{
                    img.width * (cameraSpacePoint.x + a * s) / (2 * a * s),
                    img.height - img.height * (cameraSpacePoint.y + s) / (2 * s)
            };
            tri.vertices[i] = imageSpacePoint;
            tri.verticesColor[i] = triangle3.verticesColor[i];
        }

        tri.color = triangle3.color;
        projectedTriangles.push_back(tri);
    }

    Vector2 pix;

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            Vector3 pixelColor = {0,0,0};

            for (int sub_y =0 ; sub_y<4; sub_y++){
                for (int sub_x=0; sub_x<4; sub_x++){
                    Z_buffer(x, y).z = std::numeric_limits<double>::infinity();
                    double subPixelX = x + (0.125 + 0.25 * sub_x);
                    double subPixelY = y + (0.125 + 0.25 * sub_y);
                    pix.x=subPixelX;
                    pix.y=subPixelY;
                    Vector3 color={0.5,0.5,0.5};
                    for (size_t i = 0; i < projectedTriangles.size(); i++){
                        Triangle2 triangle2=projectedTriangles[i];

                        double b_0,b_1,b_2=0;
                        double b0,b1,b2=0;
                        double depth_at_pix;
                        double inverse_depth;
                        if (IsPointInsideTriangle(pix, triangle2.vertices[0], triangle2.vertices[1], triangle2.vertices[2])) {
                            calculateProjectedBarycentricCoordinates(pix,triangle2.vertices[0],triangle2.vertices[1],triangle2.vertices[2],b_0,b_1,b_2);
                            calculateOriginalBarycentricCoordinates(worldTriangles[i].vertices[0],worldTriangles[i].vertices[1],worldTriangles[i].vertices[2],b0,b1,b2,b_0,b_1,b_2);
                            depth_at_pix= calculateDepth(b0,b1,b2,worldTriangles[i].vertices[0],worldTriangles[i].vertices[1],worldTriangles[i].vertices[2]);
                            inverse_depth=-depth_at_pix;

                            if (inverse_depth <= Z_buffer(x, y).z) {
                                Z_buffer(x, y).z = inverse_depth; // 更新深度缓冲
                                Vector3 vertexColor;
                                vertexColor=b0*triangle2.verticesColor[0]+b1*triangle2.verticesColor[1]+b2*triangle2.verticesColor[2];
                                color= vertexColor;
                            }
                        }
                    }
                    pixelColor+=color;
                }
            }
            pixelColor/=16.0;
            img(x, y) = pixelColor;
        }
    }
    return img;
}

Image3 hw_2_4(const std::vector<std::string> &params) {
    // Homework 2.4: render a scene with transformation
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;

    Image3 img(scene.camera.resolution.x,
               scene.camera.resolution.y);
    Image3 Z_buffer(img.width, img.height);

    std::vector<TriangleMesh> triangle_meshes=scene.meshes;

    for (const TriangleMesh& mesh : triangle_meshes) {
        std::vector<Triangle3> worldTriangles;
        std::vector<Triangle3> worldTriangles2;

        for (size_t i = 0; i < mesh.faces.size(); i++) {
            const Vector3& face = mesh.faces[i];
            Triangle3 triangle;
            triangle.vertices[0] = mesh.vertices[face.x];
            triangle.verticesColor[0]=mesh.vertex_colors[face.x];
            triangle.vertices[1] = mesh.vertices[face.y];
            triangle.verticesColor[1]=mesh.vertex_colors[face.y];
            triangle.vertices[2] = mesh.vertices[face.z];
            triangle.verticesColor[2]=mesh.vertex_colors[face.z];

            worldTriangles.push_back(triangle);
        }
        Real a = static_cast<Real>(img.width) / img.height;
        Matrix4x4 projection_model1 = Matrix4x4::identity();
        Matrix4x4 projection_model2 = Matrix4x4::identity();
        projection_model1(2,2)=0;
        projection_model1(2,3)=1;
        projection_model1(3,2)=-1;
        projection_model1(3,3)=0;
        projection_model2(0,0)=img.width/(2*scene.camera.s*a);
        projection_model2(0,3)=img.width/2.0;
        projection_model2(1,1)=-img.height/(2*scene.camera.s);
        projection_model2(1,3)=img.height/2.0;

        std::vector<Vector4> vertices;
        std::vector<Triangle2> projectedTriangles;

        for (auto & worldTriangle : worldTriangles){
            Triangle3 triangle3;
            Triangle2 triangle2;
            for(int i=0;i<3;i++){
                Vector4 vertex=Vector4 {worldTriangle.vertices[i].x,worldTriangle.vertices[i].y,worldTriangle.vertices[i].z,1.0};

                vertex= (mesh.model_matrix)*vertex;  //model matrix
                vertex= inverse(scene.camera.cam_to_world)*vertex;   //view matrix
                triangle3.vertices[i].x=vertex.x;
                triangle3.vertices[i].y=vertex.y;
                triangle3.vertices[i].z=vertex.z;

                vertex = projection_model1*vertex;    //project matrix 1
                vertex=(1.0/vertex.w)*vertex;
                vertex = projection_model2*vertex;    //project matrix 2
                triangle2.vertices[i].x=vertex.x;
                triangle2.vertices[i].y=vertex.y;
                triangle2.verticesColor[i]=worldTriangle.verticesColor[i];

            }
          //  calculateTriangleArea3(triangle3.vertices[0],triangle3.vertices[1],triangle3.vertices[2]);

            worldTriangles2.push_back(triangle3);
            projectedTriangles.push_back(triangle2);
        }

        Vector2 pix;

        for (int y = 0; y < img.height; y++) {
            for (int x = 0; x < img.width; x++) {
                Vector3 pixelColor = {0,0,0};

                for (int sub_y =0 ; sub_y<4; sub_y++){
                    for (int sub_x=0; sub_x<4; sub_x++){
                        Z_buffer(x, y).z = std::numeric_limits<double>::infinity();
                        double subPixelX = x + (0.125 + 0.25 * sub_x);
                        double subPixelY = y + (0.125 + 0.25 * sub_y);
                        pix.x=subPixelX;
                        pix.y=subPixelY;
                        Vector3 color={0.5,0.5,0.5};

                        for (size_t i = 0; i < projectedTriangles.size(); i++){
                            Triangle2 triangle2=projectedTriangles[i];

                            double b_0,b_1,b_2=0;
                            double b0,b1,b2=0;
                            double depth_at_pix;
                            double inverse_depth;
                            if (IsPointInsideTriangle(pix, triangle2.vertices[0], triangle2.vertices[1], triangle2.vertices[2])) {
                                calculateProjectedBarycentricCoordinates(pix,triangle2.vertices[0],triangle2.vertices[1],triangle2.vertices[2],b_0,b_1,b_2);
                                calculateOriginalBarycentricCoordinates(worldTriangles2[i].vertices[0],worldTriangles2[i].vertices[1],worldTriangles2[i].vertices[2],b0,b1,b2,b_0,b_1,b_2);
                                depth_at_pix= calculateDepth(b0,b1,b2,worldTriangles2[i].vertices[0],worldTriangles2[i].vertices[1],worldTriangles2[i].vertices[2]);
                                inverse_depth=-depth_at_pix;

                                if (inverse_depth <= Z_buffer(x, y).z) {
                                    Z_buffer(x, y).z = inverse_depth; // 更新深度缓冲
                                    Vector3 vertexColor;
                                    vertexColor=b0*triangle2.verticesColor[0]+b1*triangle2.verticesColor[1]+b2*triangle2.verticesColor[2];
                                    color= vertexColor;
                                }
                            }
                        }
                        pixelColor+=color;
                    }
                }
                pixelColor/=16.0;
                img(x, y) = pixelColor;
            }
        }

    }

    return img;
}

