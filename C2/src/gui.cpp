#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_back/imgui_impl_opengl2.h>
#include <imgui_stdlib.h>
#include <iostream>

int main() {
    static bool checkbox_value = false;
    static float slider_value = 0.5f;
    static char text_buffer[128] = "Hello, ImGui!";

    ImGui::Begin("Test Window");

    ImGui::Text("Hello from ImGui!");

    if (ImGui::Button("Click Me")) {
        std::cout << "Button clicked!\n";
    }

    ImGui::Checkbox("Enable Feature", &checkbox_value);
    ImGui::SliderFloat("Adjust Value", &slider_value, 0.0f, 1.0f);
    ImGui::InputText("Text Box", text_buffer, IM_ARRAYSIZE(text_buffer));

    ImGui::End();
}
