#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // For matrix transformations
#include <glm/gtc/type_ptr.hpp> // For converting to pointer types

/*
class Player {
public:
    float x_position = 0.0f;
    float y_position = 0.0f;
    float z_position = 0.0f; // New z-coordinate
};

// To store key states
std::unordered_map<int, bool> keyStates;

float left_bound = -1.0f;
float right_bound = 1.0f;
float bottom_bound = -1.0f;
float top_bound = 1.0f;


void processKeyInput(Player* player, float speed) {
    // Check boundaries dynamically based on updated values
    if (keyStates[GLFW_KEY_W] && player->y_position < top_bound) {
        player->y_position += speed;
    }
    if (keyStates[GLFW_KEY_S] && player->y_position > bottom_bound) {
        player->y_position -= speed;
    }
    if (keyStates[GLFW_KEY_A] && player->x_position > left_bound) {
        player->x_position -= speed;
    }
    if (keyStates[GLFW_KEY_D] && player->x_position < right_bound) {
        player->x_position += speed;
    }
    if (keyStates[GLFW_KEY_Q] && player->z_position > left_bound) {
        player->z_position -= speed;
    }
    if (keyStates[GLFW_KEY_E] && player->z_position < right_bound) {
        player->z_position += speed;
    }
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}

void key_callback(GLFWwindow* window, int key, int action) {
    if (action == GLFW_PRESS) {
        keyStates[key] = true;  // Key pressed
    }
    else if (action == GLFW_RELEASE) {
        keyStates[key] = false; // Key released
    }
}

void key_callback_wrapper(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Player* player = static_cast<Player*>(glfwGetWindowUserPointer(window));
    key_callback(window, key, action);
}


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Walking", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader ourShader("shader.vs", "shader.fs");

    float vertices[] = {
        // positions // colors
        0.25f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        -0.25f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f, 0.25f, 0.0f, 0.0f, 0.0f, 1.0f // top
    };


    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);


    // bind the VAO (it was already bound, but just to demonstrate): seeing as we only have a single VAO we can 
    // just bind it beforehand before rendering the respective triangle; this is another approach.
    glBindVertexArray(VAO);

    glViewport(0, 0, 800, 600);

    // Create Player
    Player player;

    // Set the user pointer to the player object
    glfwSetWindowUserPointer(window, &player);

    // Set the key callback
    glfwSetKeyCallback(window, key_callback_wrapper);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        processKeyInput(&player, 0.0001f); // Change speed as needed

        float scale_factor = 1.0f + player.z_position; // Scale based on z_position (adjust as necessary)
        float player_size = 0.1f; // Base size of the triangle

        ourShader.setFloat("u_offset_x", player.x_position);
        ourShader.setFloat("u_offset_y", player.y_position);
        ourShader.setFloat("u_offset_z", player.z_position);
        ourShader.setFloat("u_scale", scale_factor); // Set scale factor based on z_position

        std::vector<glm::vec3> playerVertices = {
            { player.x_position + (player_size * scale_factor), player.y_position + (player_size * scale_factor), player.z_position + player_size },
            { player.x_position - (player_size * scale_factor), player.y_position - (player_size * scale_factor), player.z_position - player_size },
            { player.x_position, player.y_position, player.z_position }
        };

        //render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, playerVertices.size() * sizeof(glm::vec3), playerVertices.data(), GL_DYNAMIC_DRAW);

         // render the triangle
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
*/
