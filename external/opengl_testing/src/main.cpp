#include <SFML/Window.hpp>
#include <glad/glad.h>

GLuint          program;
GLuint          vao;

void startup()
{
    static const char* vs_source[] = {
        "#version 420 core                                                 \n"
        "                                                                  \n"
        "void main(void)                                                   \n"
        "{                                                                 \n"
        "    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
        "                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
        "                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
        "                                                                  \n"
        "    gl_Position = vertices[gl_VertexID];                          \n"
        "}                                                                 \n"};

    static const char* fs_source[] = {
        "#version 420 core                                                 \n"
        "                                                                  \n"
        "out vec4 color;                                                   \n"
        "                                                                  \n"
        "void main(void)                                                   \n"
        "{                                                                 \n"
        "    color = vec4(1.0, 0.8, 1.0, 1.0);                             \n"
        "}                                                                 \n"};

    program   = glCreateProgram();
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, fs_source, NULL);
    glCompileShader(fs);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, vs_source, NULL);
    glCompileShader(vs);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void render()
{
    static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
    glClearBufferfv(GL_COLOR, 0, green);

    glUseProgram(program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void shutdown()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
}

int main()
{
    // create the window
    sf::ContextSettings cs;
    cs.depthBits      = 32;
    cs.attributeFlags = sf::ContextSettings::Attribute::Core;
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default,
                      cs);
    window.setVerticalSyncEnabled(true);

    // activate the window
    window.setActive(true);

    // load resources, initialize the OpenGL states, ...
    gladLoadGL();
    // run the main loop
    startup();

    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        render();

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...
    shutdown();
    return 0;
}
