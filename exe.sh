g++ -std=c++14 -g3 main.cpp entities/entity/entity.cpp entities/player/player.cpp rendering/textures/stb_image/stb_image.cpp rendering/buffers/vbo/vbo.cpp rendering/buffers/vao/vao.cpp rendering/buffers/ebo/ebo.cpp rendering/shader/shader.cpp rendering/shape/shape.cpp ~/.opengl_files/glad.c -lglfw -lrt -lm -ldl -lX11 -lpthread -lxcb -lXau -lXdmcp -lGL
if [[ $? -eq 0 ]]; then
    if [[ -f ".last_succesful_main" ]]; then
        rm .last_succesful_main
    fi
    mv a.out .main
    ./.main
else
    if [[ -f ".main" ]]; then
        mv .main .last_succesful_main
    fi
fi
