#ifndef WINDOWS_INPUT_H
#define WINDOWS_INPUT_H

#include "Input.h"

namespace Pandemonium {

	// TEMP - SHOULD NOT PANDEMONIUM_API
	class PANDEMONIUM_API WindowsInput : public Input {
	protected:
		virtual bool					IsKeyPressedImpl(int keycode) override;

		virtual bool					IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePosImpl() override;
		virtual float					GetMosueXImpl() override;
		virtual float					GetMosueYImpl() override;
	};

	// TEMP - SHOULD BE IN THE CPP
	Input* Input::s_Instance = new WindowsInput();

} // namespace Pandemonium

#endif /* WINDOWS_INPUT_H */