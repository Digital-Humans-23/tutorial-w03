//
// Created by Dongho Kang on 06.09.22.
//

#ifndef PYLOCO_VIEWER_H
#define PYLOCO_VIEWER_H

#include "crl-basic/gui/application.h"

namespace pycrl {

class Viewer : public crl::gui::ShadowApplication {
public:
    /**
     * create a full-screen viewer
     */
    explicit Viewer() : crl::gui::ShadowApplication("Pycrl Viewer") {
        init();
    }

    /**
     * create a viewer with specified width and height
     */
    explicit Viewer(int width, int height) : crl::gui::ShadowApplication("Pycrl Viewer", width, height) {
        init();
    }

    ~Viewer() override = default;

    void drawImGui() override {
        ImGui::Begin("Main Menu", NULL, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Checkbox("Show Main Menu", &showMainMenu);
        ImGui::End();

        if (showMainMenu) {
            crl::gui::ShadowApplication::drawImGui();
            ImGui::Begin("Main Menu");
            ImGui::End();
        }
    }

    void drawImPlot() override {
        ShadowApplication::drawImPlot();
    }

    void render() {
        process();
        draw();

#ifdef SINGLE_BUFFER
        glFlush();
#else
        glfwSwapBuffers(window);
#endif
        glfwPollEvents();

    }

    void readPixels(unsigned char* rgb) {
        using namespace crl::gui;
        GLCall(glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, rgb));
    }

    void close() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        crl::gui::rendering::DestroyContext();
        ImPlot::DestroyContext();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
    }

private:
    /**
     * initialization
     */
    void init() {
        this->showConsole = false;
        this->automanageConsole = true;
        this->useSeparateProcessThread = false;

        model.scale *= 0.1;

        // disable waiting for framerate of glfw window
        glfwSwapInterval(0);
    }

    /**
     * the purpose of viewer is only show robot's current state. thus, we hide process function so that no one can change this function.
     */
    void process() override {

    }

    void drawShadowCastingObjects(const crl::gui::Shader &shader) override {
        model.draw(shader, crl::gui::toV3D(normalColor), 1.f, false);
    }

    void drawObjectsWithoutShadows(const crl::gui::Shader &shader) override {
        model.draw(shader, crl::gui::toV3D(normalColor), 1.f, true);
    }

private:
    crl::gui::Model model = crl::gui::Model(CRL_DATA_FOLDER "/meshes/nanosuit.obj");
    bool showMainMenu = false;

    float selectedColor[3] = {0.8f, 0.2f, 0.1f};
    float normalColor[3] = {0.2f, 0.5f, 0.7f};
};

}  // namespace pycrl

#endif  //PYLOCO_VIEWER_H
