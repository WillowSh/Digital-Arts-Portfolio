#include "hw1.h"
#include "hw1_scenes.h"

static bool IsPointInsideTriangle( Vector2 point,  Vector2 p0,  Vector2 p1, Vector2 p2) {
    Vector2 edge0 = p1 - p0;
    Vector2 edge1 = p2 - p1;
    Vector2 edge2 = p0 - p2;

    Vector2 point0 = point - p0;
    Vector2 point1 = point - p1;
    Vector2 point2 = point - p2;

    float dot0 = edge0.x * point0.y - edge0.y * point0.x;
    float dot1 = edge1.x * point1.y - edge1.y * point1.x;
    float dot2 = edge2.x * point2.y - edge2.y * point2.x;

    return (dot0 >= 0 && dot1 >= 0 && dot2 >= 0) || (dot0 <= 0 && dot1 <= 0 && dot2 <= 0) ;
}

using namespace hw1;

Image3 hw_1_1(const std::vector<std::string> &params) {
    // Homework 1.1: render a circle at the specified
    // position, with the specified radius and color.

    Image3 img(640 /* width */, 480 /* height */);

    printf("aaaaaa");
    Vector2 center = Vector2{img.width / 2 + Real(0.5), img.height / 2 + Real(0.5)};
    Real radius = 100.0;
    Vector3 color = Vector3{0.5, 0.5, 0.5};
    for (int i = 0; i < (int)params.size(); i++) {
        if (params[i] == "-center") {
            Real x = std::stof(params[++i]);
            Real y = std::stof(params[++i]);
            center = Vector2{x, y};
        } else if (params[i] == "-radius") {
            radius = std::stof(params[++i]);
        } else if (params[i] == "-color") {
            Real r = std::stof(params[++i]);
            Real g = std::stof(params[++i]);
            Real b = std::stof(params[++i]);
            color = Vector3{r, g, b};
        }
    }

    Vector2 v0;
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            img(x, y) = Vector3{0.5, 0.5, 0.5};
            v0.x=x+0.5;
            v0.y=y+0.5;
            if(length(v0-center)<=radius){
                img(x, y) = color;
            }
        }
    }
    return img;
}

Image3 hw_1_2(const std::vector<std::string> &params) {
    // Homework 1.2: render multiple circles
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    int scene_id = std::stoi(params[0]);
    const CircleScene &scene = hw1_2_scenes[scene_id];

    Image3 img(scene.resolution.x, scene.resolution.y);

    Vector2 center;
    Real radius;
    Vector3 color;
    Vector2 v0;
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            img(x, y) = scene.background;
        }
    }

/*
    for (auto object : scene.objects) {
        center=object.center;
        radius=object.radius;
        color=object.color;
        for (int y =0 ; y < img.height; y++) {
            for (int x = 0; x <img.width; x++) {
                v0.x=x+0.5;
                v0.y=y+0.5;
                if(length(v0-center)<=radius){
                    img(x, y) = color;
                }
            }
        }
    }
*/

    for (auto object : scene.objects) {
        center=object.center;
        radius=object.radius;
        color=object.color;

        int x_min = max(0, int(center.x - radius));
        int x_max = min(img.width, int(center.x + radius));
        int y_min = max(0, int(center.y - radius));
        int y_max = min(img.height, int(center.y + radius));

        for (int y =y_min ; y <y_max; y++) {
            for (int x = x_min; x <x_max; x++) {
                v0.x=x+0.5;
                v0.y=y+0.5;
                if(length(v0-center)<=radius){
                    img(x, y) = color;
                }
            }
        }
    }

    return img;
}

Image3 hw_1_3(const std::vector<std::string> &params) {
    // Homework 1.3: render multiple shapes
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;

    Image3 img(scene.resolution.x, scene.resolution.y);
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            img(x, y) = scene.background;
        }
    }

    Vector2 v0;
    for (const Shape& shape : scene.shapes) {

        if (auto *circle = get_if<Circle>(&shape)) {
            for (int y =0 ; y < img.height; y++) {
                for (int x = 0; x <img.width; x++) {
                    v0.x=x+0.5;
                    v0.y=y+0.5;
                    if(length(v0-circle->center)<=circle->radius){
                        img(x, y) = circle->color;
                    }
                }
            }
            // do something with circle
        } else if (auto *rectangle = get_if<Rectangle>(&shape)) {
            int x_min= max(0,int(rectangle->p_min.x));
            int x_max= min(img.width,int(rectangle->p_max.x));
            int y_min= max(0,int(rectangle->p_min.y));
            int y_max= min(img.height,int(rectangle->p_max.y));
            for (int y =y_min ; y < y_max; y++) {
                for (int x =x_min; x <x_max; x++) {
                        img(x, y) = rectangle->color;
                }
            }
            // do something with rectangle
        } else if (auto *triangle = get_if<Triangle>(&shape)) {
            for (int y = 0; y < img.height; y++) {
                for (int x = 0; x < img.width; x++) {
                    Vector2 pixel(x + 0.5, y + 0.5);
                    // 检查点是否在三角形内
                    if (IsPointInsideTriangle(pixel, triangle->p0, triangle->p1, triangle->p2)) {
                        img(x, y) = triangle->color;
                    }
                }
            }

        }
    }

    return img;
}




Image3 hw_1_4(const std::vector<std::string> &params) {
    // Homework 1.4: render transformed shapes
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;

    Image3 img(scene.resolution.x, scene.resolution.y);

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            img(x, y) = scene.background;
        }
    }

    Vector2 v0;
    for (const Shape& shape : scene.shapes) {
        if (auto *circle = get_if<Circle>(&shape)) {
            for (int y =0 ; y < img.height; y++) {
                for (int x = 0; x <img.width; x++) {
                    v0.x=x+0.5;
                    v0.y=y+0.5;

                    Vector2 v_inverse;
                    Vector3 v3=Vector3{v0.x,v0.y,1.0};
                    Vector3 v4;
                    v4= inverse(get_transform(shape))*v3;
                    v_inverse.x=v4.x;
                    v_inverse.y=v4.y;

                    if(length(v_inverse-circle->center)<=circle->radius){
                        img(x, y) = circle->color;
                    }
                }
            }
            // do something with circle
        }
        else if (auto *rectangle = get_if<Rectangle>(&shape)) {
            int x_min= max(0,int(rectangle->p_min.x));
            int x_max= min(img.width,int(rectangle->p_max.x));
            int y_min= max(0,int(rectangle->p_min.y));
            int y_max= min(img.height,int(rectangle->p_max.y));
            double x_inverse;
            double y_inverse;

            for (int y = 0; y < img.height; y++) {
                for (int x = 0; x < img.width; x++) {
                    v0.x=x+0.5;
                    v0.y=y+0.5;
                    Vector3 v3=Vector3{v0.x,v0.y,1.0};
                    Vector3 v4;
                    v4= inverse(get_transform(shape))*v3;
                    x_inverse=v4.x;
                    y_inverse=v4.y;
                    if ((x_min < x_inverse) && (x_inverse < x_max) && (y_min < y_inverse) && (y_inverse < y_max)) {
                        img(x, y) = rectangle->color;
                    }
                }
            }
        }

        else if (auto *triangle = get_if<Triangle>(&shape)) {
            for (int y = 0; y < img.height; y++) {
                for (int x = 0; x < img.width; x++) {
                    Vector2 v_inverse;
                    v0.x=x+0.5;
                    v0.y=y+0.5;
                    Vector3 v3=Vector3{v0.x,v0.y,1.0};
                    Vector3 v4;
                    v4= inverse(get_transform(shape))*v3;
                    v_inverse.x=v4.x;
                    v_inverse.y=v4.y;
                    // 检查点是否在三角形内
                    if (IsPointInsideTriangle(v_inverse, triangle->p0, triangle->p1, triangle->p2)) {

                        img(x, y) = triangle->color;
                    }
                }
            }

        }

    }
    return img;
}



Image3 hw_1_5(const std::vector<std::string> &params) {
    // Homework 1.5: antialiasing
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;


    Image3 img(scene.resolution.x, scene.resolution.y);

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            img(x, y) = scene.background;
        }
    }

    Vector2 pix;

    for (const Shape& shape : scene.shapes) {
        if (auto *circle = get_if<Circle>(&shape)) {
            for (int y =0 ; y < img.height; y++) {
                for (int x = 0; x <img.width; x++) {
                    Vector3 pixelColor = {0,0,0};
                    bool hit= false;
                    for (int sub_y =0 ; sub_y<4; sub_y++){
                        for (int sub_x=0; sub_x<4; sub_x++){
                            double subPixelX = x + (0.125 + 0.25 * sub_x);
                            double subPixelY = y + (0.125 + 0.25 * sub_y);
                            pix.x=subPixelX;
                            pix.y=subPixelY;
                            Vector2 v_inverse;
                            Vector3 v3=Vector3{pix.x,pix.y,1.0};
                            Vector3 v4;
                            v4= inverse(get_transform(shape))*v3;
                            v_inverse.x=v4.x;
                            v_inverse.y=v4.y;

                            if(length(v_inverse-circle->center)<=circle->radius){
                                hit= true;
                                pixelColor += circle->color;
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
            // do something with circle
        }
        else if (auto *rectangle = get_if<Rectangle>(&shape)) {
            int x_min= max(0,int(rectangle->p_min.x));
            int x_max= min(img.width,int(rectangle->p_max.x));
            int y_min= max(0,int(rectangle->p_min.y));
            int y_max= min(img.height,int(rectangle->p_max.y));

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
                            Vector2 v_inverse;
                            Vector3 v3=Vector3{pix.x,pix.y,1.0};
                            Vector3 v4;
                            v4= inverse(get_transform(shape))*v3;
                            v_inverse.x=v4.x;
                            v_inverse.y=v4.y;

                            if ((x_min <= v_inverse.x) && (v_inverse.x <= x_max) && (y_min <= v_inverse.y) && (v_inverse.y <= y_max)) {
                                hit= true;
                                pixelColor += rectangle->color;
                            } else{
                                pixelColor+=img(x,y);
                            }
                        }
                    }
                    if(hit){
                        pixelColor/=16.00;
                        img(x, y) = pixelColor;
                    }
                }
            }
        }

        else if (auto *triangle = get_if<Triangle>(&shape)) {
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
                            Vector2 v_inverse;
                            Vector3 v3=Vector3{pix.x,pix.y,1.0};
                            Vector3 v4;
                            v4= inverse(get_transform(shape))*v3;
                            v_inverse.x=v4.x;
                            v_inverse.y=v4.y;

                            if (IsPointInsideTriangle(v_inverse, triangle->p0, triangle->p1, triangle->p2)) {
                                hit= true;
                                pixelColor += triangle->color;
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

    }
    return img;
}

Image3 hw_1_6(const std::vector<std::string> &params) {
    // Homework 1.6: alpha blending
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;

    Image3 img(scene.resolution.x, scene.resolution.y);

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            img(x, y) = scene.background;
        }
    }

    Vector2 v0;
    for (const Shape& shape : scene.shapes) {

        if (auto *circle = get_if<Circle>(&shape)) {
            for (int y =0 ; y < img.height; y++) {
                for (int x = 0; x <img.width; x++) {
                    v0.x=x+0.5;
                    v0.y=y+0.5;
                    if(length(v0-circle->center)<=circle->radius){
                        img(x, y) = (circle->color)*(circle->alpha)+img(x,y)*(1-(circle->alpha));
                    }
                }
            }
            // do something with circle
        } else if (auto *rectangle = get_if<Rectangle>(&shape)) {
            int x_min= max(0,int(rectangle->p_min.x));
            int x_max= min(img.width,int(rectangle->p_max.x));
            int y_min= max(0,int(rectangle->p_min.y));
            int y_max= min(img.height,int(rectangle->p_max.y));
            for (int y =y_min ; y < y_max; y++) {
                for (int x =x_min; x <x_max; x++) {
                    img(x, y) = (rectangle->color)*(rectangle->alpha)+img(x,y)*(1-(rectangle->alpha));
                }
            }
            // do something with rectangle
        } else if (auto *triangle = get_if<Triangle>(&shape)) {
            for (int y = 0; y < img.height; y++) {
                for (int x = 0; x < img.width; x++) {
                    Vector2 pixel(x + 0.5, y + 0.5);
                    if (IsPointInsideTriangle(pixel, triangle->p0, triangle->p1, triangle->p2)) {
                        img(x, y) = (triangle->color)*(triangle->alpha)+img(x,y)*(1-(triangle->alpha));
                    }
                }
            }

        }
    }

    return img;
}
/*  Image3 hw_1_7 is the same as hw_1_5
 * using "./balboa -hw 1_5 ../scenes/hw1/miffy.json"
 */

Image3 hw_1_8(const std::vector<std::string> &params) {
    // Homework 1.3: render multiple shapes
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;

    Image3 img(scene.resolution.x, scene.resolution.y);
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            img(x, y) = scene.background;
        }
    }

    for (const Shape& shape : scene.shapes) {

        if (auto *line = get_if<Line>(&shape)) {

            Real width=line->width;
            Vector2 start=line->p0;
            Vector2 end=line->p1;

            int dx = int(end.x) - int(start.x);
            int dy = int(end.y) - int(start.y);
            double length = sqrt(dx * dx + dy * dy);
            double angle = atan2(dy, dx);

            for (int w = -int(width) / 2; w < width / 2; w++) {
                // Calculate the offset from the center of the line segment
                int xOffset = static_cast<int>(w * sin(angle));
                int yOffset = static_cast<int>(w * cos(angle));

                for (int t = 0; t < static_cast<int>(length); t++) {
                    int x = int(start.x) + static_cast<int>(t * cos(angle)) + xOffset;
                    int y = int(start.y) + static_cast<int>(t * sin(angle)) + yOffset;

                    if (x >= 0 && x < img.width && y >= 0 && y < img.height) {
                        img(x, y) = line->color;
                    }
                }
            }
        } else if (auto *quadraticBezier = get_if<QuadraticBezier>(&shape)) {

            Real width = quadraticBezier->width;
            Vector2 p0 = quadraticBezier->p0;
            Vector2 p1 = quadraticBezier->p1;
            Vector2 p2 = quadraticBezier->p2;
            int resolution=1000;

            for (int t = 0; t <= resolution; t++) {
                double normalized_t = static_cast<double>(t) / static_cast<double>(resolution);
                Vector2 point = (1.0 - normalized_t) * (1.0 - normalized_t) * p0 + 2.0 * (1.0 - normalized_t) * normalized_t * p1 + normalized_t * normalized_t * p2;

                Vector2 tangent = 2.0 * (1.0 - normalized_t) * (p1 - p0) + 2.0 * normalized_t * (p2 - p1);
                Vector2 normal(-tangent.y, tangent.x);
                normal = normalize(normal);  // Normalize the normal vector

                for (int w = -width / 2; w < width / 2; w++) {
                    Vector2 offset = normal * Real(w);
                    int x = static_cast<int>(point.x + offset.x);
                    int y = static_cast<int>(point.y + offset.y);
                    if (x >= 0 && x < img.width && y >= 0 && y < img.height) {
                        img(x, y) = quadraticBezier->color;
                    }
                }
            }

        }else if (auto *cubicBezier = get_if<CubicBezier>(&shape)) {

            Real width = cubicBezier->width;
            Vector2 p0 = cubicBezier->p0;
            Vector2 p1 = cubicBezier->p1;
            Vector2 p2 = cubicBezier->p2;
            Vector2 p3 = cubicBezier->p3;
            int resolution=1000;
            for (int t = 0; t <= resolution; t++) {
                double normalized_t = static_cast<double>(t) / static_cast<double>(resolution);
                Vector2 point = (1.0 - normalized_t) * (1.0 - normalized_t) * (1.0 - normalized_t) * p0 +
                                3.0 * (1.0 - normalized_t) * (1.0 - normalized_t) * normalized_t * p1 +
                                3.0 * (1.0 - normalized_t) * normalized_t * normalized_t * p2 +
                                normalized_t * normalized_t * normalized_t * p3;


                Vector2 tangent = 3.0 * (1.0 - normalized_t) * (1.0 - normalized_t) * (p1 - p0) +
                                  6.0 * (1.0 - normalized_t) * normalized_t * (p2 - p1) +
                                  3.0 * normalized_t * normalized_t * (p3 - p2);
                Vector2 normal(-tangent.y, tangent.x);
                normal = normalize(normal);

                for (int w = -width / 2; w < width / 2; w++) {
                    Vector2 offset = normal * Real(w);
                    int x = static_cast<int>(point.x + offset.x);
                    int y = static_cast<int>(point.y + offset.y);
                    if (x >= 0 && x < img.width && y >= 0 && y < img.height) {
                        img(x, y) = cubicBezier->color;
                    }
                }
            }

        }
    }
    return img;
}