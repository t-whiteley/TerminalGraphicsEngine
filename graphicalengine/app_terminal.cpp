#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <unistd.h>
#include "libs/LINALG.h"
#include "libs/GRAPHICS.h"


// g++ -std=c++11 -o app app_terminal.cpp libs/LINALG.cpp libs/GRAPHICS.cpp


int main() {
    Screen S(175, 60, 2, 0.1, 1000);
    Camera C;

    struct Mesh m1_obj_space = build_cube_mesh(0, 0, -3, 0, 0, 0, 1);
    struct Mesh m1_world_space = build_dummy_mesh(m1_obj_space);
    struct Mesh m1_cam_space = build_dummy_mesh(m1_obj_space);
    struct Mesh m1_viewvol_space = build_dummy_mesh(m1_obj_space);

    char ch;
    float d_theta = 0.05;
    float cam_dx = 0, cam_dy = 0, cam_dz = 0, cam_d_pitch = 0, cam_d_yaw = 0;
    float rotation_rate = 0.1, displacement_rate = 0.1;

    while (true) {

        // Pan the camera from user input
        // std::cout << "Change: \n";
        // std::cin >> ch;
        // switch (ch) {
        //     case 'w': cam_dz = displacement_rate; break;
        //     case 's': cam_dz = -displacement_rate; break;
        //     case 'd': cam_dx = displacement_rate; break;
        //     case 'a': cam_dx = -displacement_rate; break;
        //     case 'u': cam_dy = displacement_rate; break;
        //     case 'i': cam_dy = -displacement_rate; break;
        //     case 'm': cam_d_pitch = rotation_rate; break;
        //     case 'n': cam_d_pitch = -rotation_rate; break;
        //     case 'k': cam_d_yaw = rotation_rate; break;
        //     case 'j': cam_d_yaw = -rotation_rate; break;
        //     default:  break;
        // }
        // if (ch == 'q')
        //     break;

        C.control_cam(cam_dx, cam_dy, -cam_dz, cam_d_pitch, cam_d_yaw);
        transform_mesh(0, 0, 0, d_theta, d_theta/2, 0, 0, m1_obj_space);
        mesh_to_world_space(m1_obj_space, m1_world_space);
        C.mesh_to_cam_space(m1_world_space, m1_cam_space);
        S.mesh_to_view_volume(m1_cam_space, m1_viewvol_space);


        S.draw_mesh_Terminal(m1_viewvol_space);
        S.display();
        S.refresh();


        cam_dx = cam_dy = cam_dz = cam_d_pitch = cam_d_yaw = 0;
        float dt = (1.0f / 60) * 1000000; // 60 fps
        usleep(dt*2);
    }




}