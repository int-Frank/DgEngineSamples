
#include "Options.h"
#include "GUIDemo.h"
#include "Application.h"
#include "System_GUI.h"
#include "System_Input.h"

#include "GUI.h"
#include "GUI_Window.h"
#include "GUI_Button.h"
#include "GUI_Text.h"
#include "GUI_Checkbox.h"
#include "GUI_Slider.h"

using namespace DgE;
using namespace DgE::GUI;

MAKE_SYSTEM_DEFINITION(GUIDemo)

void GUIDemo::OnAttach()
{
  m_textColour = 0xFFFFFFFF;

  BuildGUI();
  BindInput();
}

void GUIDemo::BuildGUI()
{
  System_GUI * pSysUI = static_cast<System_GUI *>(Application::Instance()->GetSystem(System_GUI::GetStaticID()));
  if (!pSysUI)
  {
    LOG_ERROR("Couldn't find input layer!");
    return;
  }

  // Main window
  Window * pMainWindow = Window::Create(nullptr, {70.f, 40.f}, {735.f, 450.f});

  //// Text wrapping options
  Checkbox *pChkbox = Checkbox::Create(pMainWindow, {12.0f, 60.0f}, true);
  pChkbox->BindCheckedChanged([](bool checked)
    {
      LOG_INFO("Checked = {0}", checked ? 1 : 0);
    });

  SliderFloat *pSliderFloat = SliderFloat::Create(pMainWindow, vec2(20.0f, 100.0f), 100.0f, 0.0f, 42.0f, 1.0f, false);
  SliderFloat *pSliderInt = SliderFloat::Create(pMainWindow, vec2(20.0f, 140.0f), 100.0f, 0, 5, 1, true);

  Button * pBtnReset = Button::Create(nullptr, "Reset", {10.f, 10.f}, {70.f, 30.f});
  pBtnReset->BindSelect([]()
    {
      LOG_INFO("Pressed");
    });

  pMainWindow->Add(pBtnReset);
  pMainWindow->Add(pChkbox);
  pMainWindow->Add(pSliderFloat);
  pMainWindow->Add(pSliderInt);

  // Hooking it all up
  pSysUI->AddWidget(pMainWindow);
}

void GUIDemo::BindInput()
{
  System_Input * layer = static_cast<DgE::System_Input *>(Application::Instance()->GetSystem(DgE::System_Input::GetStaticID()));
  if (!layer)
  {
    LOG_ERROR("Couldn't find input layer!");
    return;
  }

  // TODO A helper function should live in the Engine to set up default GUI bindings
  layer->AddBinding(DgE::IC_MOUSE_MOTION, DgE::IE_VALUE_CHANGE,
    [](DgE::Message const * pMsg, void *)
    {
      DgE::Message_Input_Mouse * pIn = (DgE::Message_Input_Mouse *)pMsg;
      DgE::Message_GUI_PointerMove * pOut = nullptr;
      EMPLACE_POST(DgE::Message_GUI_PointerMove, pOut);
      pOut->x = pIn->x;
      pOut->y = pIn->y;
    });

  layer->AddBinding(DgE::IC_KEY_Q, DgE::IE_BUTTON_DOWN,
    [](DgE::Message const *, void *)
    {
      EMPLACE_POST(DgE::Message_Quit);
    });

  layer->AddBinding(DgE::IC_MOUSE_BUTTON_LEFT, DgE::IE_BUTTON_DOWN,
    [](DgE::Message const * pMsg, void *)
    {
      DgE::Message_Input_Mouse * pIn = (DgE::Message_Input_Mouse *)pMsg;
      DgE::Message_GUI_PointerDown * pOut = nullptr;
      EMPLACE_POST(DgE::Message_GUI_PointerDown, pOut);
      pOut->x = pIn->x;
      pOut->y = pIn->y;
    });

  layer->AddBinding(DgE::IC_MOUSE_BUTTON_LEFT, DgE::IE_BUTTON_UP,
    [](DgE::Message const * pMsg, void *)
    {
      DgE::Message_Input_Mouse * pIn = (DgE::Message_Input_Mouse *)pMsg;
      DgE::Message_GUI_PointerUp * pOut = nullptr;
      EMPLACE_POST(DgE::Message_GUI_PointerUp, pOut);
      pOut->x = pIn->x;
      pOut->y = pIn->y;
    });
}