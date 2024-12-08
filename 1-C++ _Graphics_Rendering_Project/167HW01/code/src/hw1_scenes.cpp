#include "hw1_scenes.h"
#include "3rdparty/json.hpp"
#include "flexception.h"
#include "matrix.h"
#include <fstream>

using json = nlohmann::json;

namespace hw1 {

CircleScene hw1_2_scene_0 = {
    {640, 360}, // resolution
    {0.5, 0.5, 0.5}, // background
    { // center, radius, color
        {{320, 180}, 160, {0.3, 0.5, 0.8}},
        {{150,  80},  80, {0.8, 0.3, 0.5}},
        {{490,  80},  80, {0.8, 0.3, 0.5}},
    }
};

CircleScene hw1_2_scene_1 = {
    {1280, 720}, // resolution
    {0.5, 0.7, 0.5}, // background
    { // center, radius, color
        {{0, 0}, 720, {0.2, 0.2, 0.8}},
        {{1280, 0}, 720, {0.8, 0.2, 0.5}},
        {{640, 500}, 80, {0.8, 0.8, 0.2}},
    }
};

CircleScene hw1_2_scene_2 = {
    {350, 650}, // resolution
    {0.7, 0.2, 0.3}, // background
    { // center, radius, color
        {{100, 200}, 200, {0.2, 0.2, 0.8}},
        {{150, 300}, 220, {0.8, 0.2, 0.2}},
        {{200, 400}, 240, {0.2, 0.8, 0.2}},
        {{250, 500}, 260, {0.8, 0.2, 0.8}},
        {{300, 600}, 280, {0.2, 0.8, 0.8}},
        {{300, 600}, 280, {0.2, 0.8, 0.8}}
    }
};

CircleScene hw1_2_scene_3 = {
    {512, 512}, // resolution
    {0.5, 0.5, 0.3}, // background
    { // center, radius, color
        {{256, 256}, 100, {0.8, 0.8, 0.8}},
        {{128, 128}, 100, {0.2, 0.2, 0.2}},
        {{384, 128}, 100, {0.2, 0.2, 0.2}},
        {{384, 384}, 100, {0.2, 0.2, 0.2}},
        {{128, 384}, 100, {0.2, 0.2, 0.2}}
    }
};

CircleScene hw1_2_scene_4 = {
    {720, 512}, // resolution
    {0.5, 0.5, 0.5}, // background
    { // center, radius, color
        {{150, 150}, 150, {0.3, 0.3, 0.8}},
        {{360, 150}, 150, {0.2, 0.2, 0.2}},
        {{570, 150}, 150, {0.8, 0.3, 0.3}},
        {{255, 300}, 150, {0.3, 0.8, 0.8}},
        {{465, 300}, 150, {0.3, 0.8, 0.3}}
    }
};

CircleScene hw1_2_scenes[] = {
    hw1_2_scene_0,
    hw1_2_scene_1,
    hw1_2_scene_2,
    hw1_2_scene_3,
    hw1_2_scene_4
};

Matrix3x3 parse_transformation(const json &node) {
    // Homework 1.4: parse a sequence of linear transformation and 
    // combine them into an affine matrix
    Matrix3x3 F = Matrix3x3::identity();
    auto transform_it = node.find("transform");
    if (transform_it == node.end()) {
        // Transformation not specified, return identity.
        return F;
    }

    for (auto it = transform_it->begin(); it != transform_it->end(); it++) {
        if (auto scale_it = it->find("scale"); scale_it != it->end()) {
            Vector2 scale = Vector2{
                (*scale_it)[0], (*scale_it)[1]
            };
            Matrix3x3 m1 = Matrix3x3::identity(); // set matrix to identity
            Vector3 v = Vector3{scale.x, scale.y,1.0};
            m1(0,0)=scale.x;
            m1(1,1)=scale.y;
            F=m1*F;
            UNUSED(scale); // silence warning, feel free to remove it
        } else if (auto rotate_it = it->find("rotate"); rotate_it != it->end()) {
            Real angle = *rotate_it;
            Matrix3x3 m2 = Matrix3x3::identity(); // set matrix to identity
            double radians = angle * M_PI / 180.0;
            m2(0,0)= cos(radians);
            m2(1,1)= cos(radians);
            m2(0,1)=-sin(radians);
            m2(1,0)= sin(radians);
            F=m2*F;
            UNUSED(angle); // silence warning, feel free to remove it
        } else if (auto translate_it = it->find("translate"); translate_it != it->end()) {
            Vector2 translate = Vector2{
                (*translate_it)[0], (*translate_it)[1]
            };
            Matrix3x3 m3 = Matrix3x3::identity(); // set matrix to identity
            m3(0,2)= translate.x;
            m3(1,2)= translate.y;
            F=m3*F;
            UNUSED(translate); // silence warning, feel free to remove it
        } else if (auto shearx_it = it->find("shear_x"); shearx_it != it->end()) {
            Real shear_x = *shearx_it;
            Matrix3x3 m4 = Matrix3x3::identity(); // set matrix to identity
            m4(0,1)= shear_x;
            F=m4*F;
            UNUSED(shear_x); // silence warning, feel free to remove it
        } else if (auto sheary_it = it->find("shear_y"); sheary_it != it->end()) {
            Real shear_y = *sheary_it;
            Matrix3x3 m5= Matrix3x3::identity(); // set matrix to identity
            m5(1,0)= shear_y;
            F=m5*F;
            UNUSED(shear_y); // silence warning, feel free to remove it
        }
    }
    return F;
}

Scene parse_scene(const fs::path &filename) {
    std::ifstream f(filename.string().c_str());
    json data = json::parse(f);
    Scene scene;
    
    auto res = data.find("resolution");
    if (res == data.end()) {
        Error("Scene does not contain the field \"resolution\".");
        return scene;
    }
    scene.resolution = Vector2i{(*res)[0], (*res)[1]};
    
    auto background = data.find("background");
    scene.background = Vector3{1, 1, 1};
    if (background != data.end()) {
        scene.background = Vector3{
            (*background)[0], (*background)[1], (*background)[2]
        };
    }

    auto objects = data.find("objects");
    for (auto it = objects->begin(); it != objects->end(); it++) {
        if (it->find("type") == it->end()) {
            Error("Object with undefined type.");
        }
        if ((*it)["type"] == "circle") {
            Vector2 center{0, 0};
            Real radius = 1;
            Vector3 color{0, 0, 0};
            Real alpha = 1;

            auto center_it = it->find("center");
            if (center_it != it->end()) {
                center = Vector2{
                    (*center_it)[0], (*center_it)[1]
                };
            }
            auto radius_it = it->find("radius");
            if (radius_it != it->end()) {
                radius = (*radius_it);
            }
            auto color_it = it->find("color");
            if (color_it != it->end()) {
                color = Vector3{
                    (*color_it)[0], (*color_it)[1], (*color_it)[2]
                };
            }
            auto alpha_it = it->find("alpha");
            if (alpha_it != it->end()) {
                alpha = (*alpha_it);
            }
            Matrix3x3 transform = parse_transformation(*it);
            scene.shapes.push_back(Circle{center, radius, color, alpha, transform});
        } else if ((*it)["type"] == "rectangle") {
            Vector2 p_min{0, 0};
            Vector2 p_max{1, 1};
            Vector3 color{0, 0, 0};
            Real alpha = 1;

            auto p_min_it = it->find("p_min");
            if (p_min_it != it->end()) {
                p_min = Vector2{
                    (*p_min_it)[0], (*p_min_it)[1]
                };
            }
            auto p_max_it = it->find("p_max");
            if (p_max_it != it->end()) {
                p_max = Vector2{
                    (*p_max_it)[0], (*p_max_it)[1]
                };
            }
            auto color_it = it->find("color");
            if (color_it != it->end()) {
                color = Vector3{
                    (*color_it)[0], (*color_it)[1], (*color_it)[2]
                };
            }
            auto alpha_it = it->find("alpha");
            if (alpha_it != it->end()) {
                alpha = (*alpha_it);
            }
            Matrix3x3 transform = parse_transformation(*it);
            scene.shapes.push_back(Rectangle{p_min, p_max, color, alpha, transform});
        } else if ((*it)["type"] == "triangle") {
            Vector2 p0{0, 0};
            Vector2 p1{1, 0};
            Vector2 p2{0, 1};
            Vector3 color{0, 0, 0};
            Real alpha = 1;

            auto p0_it = it->find("p0");
            if (p0_it != it->end()) {
                p0 = Vector2{
                    (*p0_it)[0], (*p0_it)[1]
                };
            }
            auto p1_it = it->find("p1");
            if (p1_it != it->end()) {
                p1 = Vector2{
                    (*p1_it)[0], (*p1_it)[1]
                };
            }
            auto p2_it = it->find("p2");
            if (p2_it != it->end()) {
                p2 = Vector2{
                    (*p2_it)[0], (*p2_it)[1]
                };
            }
            auto color_it = it->find("color");
            if (color_it != it->end()) {
                color = Vector3{
                    (*color_it)[0], (*color_it)[1], (*color_it)[2]
                };
            }
            auto alpha_it = it->find("alpha");
            if (alpha_it != it->end()) {
                alpha = (*alpha_it);
            }
            Matrix3x3 transform = parse_transformation(*it);
            scene.shapes.push_back(Triangle{p0, p1, p2, color, alpha, transform});
        }
        else if ((*it)["type"] == "line") {
            Real width=3;
            Vector2 p0{1, 0};
            Vector2 p1{0, 1};
            Vector3 color{0, 0, 0};
            Real alpha = 1;

            auto width_it = it->find("width");
            if (width_it != it->end()) {
                width = (*width_it);
            }
            auto p0_it = it->find("p0");
            if (p0_it != it->end()) {
                p0 = Vector2{
                        (*p0_it)[0], (*p0_it)[1]
                };
            }
            auto p1_it = it->find("p1");
            if (p1_it != it->end()) {
                p1 = Vector2{
                        (*p1_it)[0], (*p1_it)[1]
                };
            }
            auto color_it = it->find("color");
            if (color_it != it->end()) {
                color = Vector3{
                        (*color_it)[0], (*color_it)[1], (*color_it)[2]
                };
            }
            auto alpha_it = it->find("alpha");
            if (alpha_it != it->end()) {
                alpha = (*alpha_it);
            }
            Matrix3x3 transform = parse_transformation(*it);
            scene.shapes.push_back(Line{width, p0, p1, color, alpha, transform});
        }
        else if ((*it)["type"] == "quadraticBezier") {
            Real width=3;
            Vector2 p0{1, 0};
            Vector2 p1{0, 10};
            Vector2 p2{5, 5};
            Vector3 color{0, 0, 0};
            Real alpha = 1;

            auto width_it = it->find("width");
            if (width_it != it->end()) {
                width = (*width_it);
            }
            auto p0_it = it->find("p0");
            if (p0_it != it->end()) {
                p0 = Vector2{
                        (*p0_it)[0], (*p0_it)[1]
                };
            }
            auto p1_it = it->find("p1");
            if (p1_it != it->end()) {
                p1 = Vector2{
                        (*p1_it)[0], (*p1_it)[1]
                };
            }auto p2_it = it->find("p2");
            if (p2_it != it->end()) {
                p2 = Vector2{
                        (*p2_it)[0], (*p2_it)[1]
                };
            }
            auto color_it = it->find("color");
            if (color_it != it->end()) {
                color = Vector3{
                        (*color_it)[0], (*color_it)[1], (*color_it)[2]
                };
            }
            auto alpha_it = it->find("alpha");
            if (alpha_it != it->end()) {
                alpha = (*alpha_it);
            }
            Matrix3x3 transform = parse_transformation(*it);
            scene.shapes.push_back(QuadraticBezier{width, p0, p1,p2, color, alpha, transform});
        }else if ((*it)["type"] == "cubicBezier") {
            Real width=3;
            Vector2 p0{1, 0};
            Vector2 p1{0, 10};
            Vector2 p2{5, 5};
            Vector2 p3{5, 15};
            Vector3 color{0, 0, 0};
            Real alpha = 1;

            auto width_it = it->find("width");
            if (width_it != it->end()) {
                width = (*width_it);
            }
            auto p0_it = it->find("p0");
            if (p0_it != it->end()) {
                p0 = Vector2{
                        (*p0_it)[0], (*p0_it)[1]
                };
            }
            auto p1_it = it->find("p1");
            if (p1_it != it->end()) {
                p1 = Vector2{
                        (*p1_it)[0], (*p1_it)[1]
                };
            }
            auto p2_it = it->find("p2");
            if (p2_it != it->end()) {
                p2 = Vector2{
                        (*p2_it)[0], (*p2_it)[1]
                };
            }
            auto p3_it = it->find("p3");
            if (p3_it != it->end()) {
                p3 = Vector2{
                        (*p3_it)[0], (*p3_it)[1]
                };
            }
            auto color_it = it->find("color");
            if (color_it != it->end()) {
                color = Vector3{
                        (*color_it)[0], (*color_it)[1], (*color_it)[2]
                };
            }
            auto alpha_it = it->find("alpha");
            if (alpha_it != it->end()) {
                alpha = (*alpha_it);
            }
            Matrix3x3 transform = parse_transformation(*it);
            scene.shapes.push_back(CubicBezier{width, p0, p1,p2, p3,color, alpha, transform});
        }
    }

    return scene;
}

std::ostream& operator<<(std::ostream &os, const Shape &shape) {
    os << "Shape[type=";
    if (auto *circle = std::get_if<Circle>(&shape)) {
        os << "Circle, " << 
              "center=" << circle->center << ", " <<
              "radius=" << circle->radius << ", " <<
              "color=" << circle->color << ", " <<
              "transform=" << std::endl << circle->transform << "]";
    } else if (auto *rectangle = std::get_if<Rectangle>(&shape)) {
        os << "Rectangle, " << 
              "p_min=" << rectangle->p_min << ", " <<
              "p_max=" << rectangle->p_max << ", " <<
              "color=" << rectangle->color << ", " <<
              "transform=" << std::endl<< rectangle->transform << "]";
    } else if (auto *triangle = std::get_if<Triangle>(&shape)) {
        os << "Triangle, " << 
              "p0=" << triangle->p0 << ", " <<
              "p1=" << triangle->p1 << ", " <<
              "p2=" << triangle->p2 << ", " <<
              "color=" << triangle->color << ", " <<
              "transform=" << std::endl << triangle->transform << "]";
    }else if (auto *line = std::get_if<Line>(&shape)) {
        os << "Line, " <<
           "p0=" << line->width << ", " <<
           "p1=" << line->p0 << ", " <<
           "p2=" << line->p1 << ", " <<
           "color=" << line->color << ", " <<
           "transform=" << std::endl << line->transform << "]";
    } else {
        // Likely an unhandled case.
        os << "Unknown]";
    }
    return os;
}

std::ostream& operator<<(std::ostream &os, const Scene &scene) {
    os << "Scene[";
    os << "Resolution:" << scene.resolution << std::endl;
    os << "\tBackground:" << scene.background << std::endl;
    for (auto s : scene.shapes) {
        os << "\t" << s << std::endl;
    }
    os << "]";
    return os;
}

} // namespace hw1