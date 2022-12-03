#ifndef IM_GUI_LAYER_H
#define IM_GUI_LAYER_H

#include "Core.h"
#include "Layer.h"

#include "ApplicationEvent.h"
#include "KeyEvent.h"
#include "MouseEvent.h"

namespace Pandemonium {
	class PANDEMONIUM_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void		 Begin();
		void		 End();
	private:
	private:
		float m_Time = 0.0f;
	};
} // namespace Pandemonium

#endif /* IM_GUI_LAYER_H */