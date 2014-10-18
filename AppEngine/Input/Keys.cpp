
#include "Keys.h"

namespace AppEngine
{
	String Keys::GetKeyText(int keyNum)
	{
		switch (keyNum)
		{
			case A: return "a";
			case B: return "b";
			case C: return "c";
			case D: return "d";
			case E: return "e";
			case F: return "f";
			case G: return "g";
			case H: return "h";
			case I: return "i";
			case J: return "j";
			case K: return "k";
			case L: return "l";
			case M: return "m";
			case N: return "n";
			case O: return "o";
			case P: return "p";
			case Q: return "q";
			case R: return "r";
			case S: return "s";
			case T: return "t";
			case U: return "u";
			case V: return "v";
			case W: return "w";
			case X: return "x";
			case Y: return "y";
			case Z: return "z";
			case NUM_0: return "0";
			case NUM_1: return "1";
			case NUM_2: return "2";
			case NUM_3: return "3";
			case NUM_4: return "4";
			case NUM_5: return "5";
			case NUM_6: return "6";
			case NUM_7: return "7";
			case NUM_8: return "8";
			case NUM_9: return "9";
			case ESCAPE: return "esc";
			case CTRL_LEFT: return "ctrl";
			case SHIFT_LEFT: return "shift";
			case ALT_LEFT: return "alt";
			case WINDOWS_LEFT: return "windows";
			case CTRL_RIGHT: return "ctrl";
			case SHIFT_RIGHT: return "shift";
			case ALT_RIGHT: return "alt";
			case WINDOWS_RIGHT: return "windows";
			case CONTEXT_MENU: return "context";
			case OPENBRACKET: return "[";
			case CLOSEBRACKET: return "]";
			case SEMICOLON: return ";";
			case COMMA: return ",";
			case PERIOD: return ".";
			case QUOTE: return "\"";
			case FORWARDSLASH: return "/";
			case BACKSLASH: return "\\";
			case EQUALS: return "=";
			case DASH: return "-";
			case SPACE: return "space";
			case ENTER: return "enter";
			case BACKSPACE: return "backspace";
			case TAB: return "tab";
			case PAGEUP: return "pg up";
			case PAGEDOWN: return "pg dn";
			case END: return "end";
			case HOME: return "home";
			case INS: return "insert";
			case DEL: return "delete";
			case ADD: return "+";
			case SUBTRACT: return "-";
			case MULTIPLY: return "*";
			case DIVIDE: return "/";
			case LEFTARROW: return "left arrow";
			case RIGHTARROW: return "right arrow";
			case UPARROW: return "up arrow";
			case DOWNARROW: return "down arrow";
			case NUMPAD_0: return "[0]";
			case NUMPAD_1: return "[1]";
			case NUMPAD_2: return "[2]";
			case NUMPAD_3: return "[3]";
			case NUMPAD_4: return "[4]";
			case NUMPAD_5: return "[5]";
			case NUMPAD_6: return "[6]";
			case NUMPAD_7: return "[7]";
			case NUMPAD_8: return "[8]";
			case NUMPAD_9: return "[9]";
			case F1: return "f1";
			case F2: return "f2";
			case F3: return "f3";
			case F4: return "f4";
			case F5: return "f5";
			case F6: return "f6";
			case F7: return "f7";
			case F8: return "f8";
			case F9: return "f9";
			case F10: return "f10";
			case F11: return "f11";
			case F12: return "f12";
			case F13: return "f13";
			case F14: return "f14";
			case F15: return "f15";
			case PAUSE: return "pause";
		}
		return "Unknown Key";
	}
	
	int Keys::SDLK_to_KeyCode(int code)
	{
		switch(code)
		{
			case SDLK_a: return A;
			case SDLK_b: return B;
			case SDLK_c: return C;
			case SDLK_d: return D;
			case SDLK_e: return E;
			case SDLK_f: return F;
			case SDLK_g: return G;
			case SDLK_h: return H;
			case SDLK_i: return I;
			case SDLK_j: return J;
			case SDLK_k: return K;
			case SDLK_l: return L;
			case SDLK_m: return M;
			case SDLK_n: return N;
			case SDLK_o: return O;
			case SDLK_p: return P;
			case SDLK_q: return Q;
			case SDLK_r: return R;
			case SDLK_s: return S;
			case SDLK_t: return T;
			case SDLK_u: return U;
			case SDLK_v: return V;
			case SDLK_w: return W;
			case SDLK_x: return X;
			case SDLK_y: return Y;
			case SDLK_z: return Z;
			case SDLK_0: return NUM_0;
			case SDLK_1: return NUM_1;
			case SDLK_2: return NUM_2;
			case SDLK_3: return NUM_3;
			case SDLK_4: return NUM_4;
			case SDLK_5: return NUM_5;
			case SDLK_6: return NUM_6;
			case SDLK_7: return NUM_7;
			case SDLK_8: return NUM_8;
			case SDLK_9: return NUM_9;
			case SDLK_ESCAPE: return ESCAPE;
			case SDLK_LCTRL: return CTRL_LEFT;
			case SDLK_LSHIFT: return SHIFT_LEFT;
			case SDLK_LALT: return ALT_LEFT;
			case SDLK_LGUI: return WINDOWS_LEFT;
			case SDLK_RCTRL: return CTRL_RIGHT;
			case SDLK_RSHIFT: return SHIFT_RIGHT;
			case SDLK_RALT: return ALT_RIGHT;
			case SDLK_RGUI: return WINDOWS_RIGHT;
			case SDLK_MENU: return CONTEXT_MENU;
			case SDLK_LEFTBRACKET: return OPENBRACKET;
			case SDLK_RIGHTBRACKET: return CLOSEBRACKET;
			case SDLK_SEMICOLON: return SEMICOLON;
			case SDLK_COMMA: return COMMA;
			case SDLK_PERIOD: return PERIOD;
			case SDLK_QUOTE: return QUOTE;
			case SDLK_SLASH: return FORWARDSLASH;
			case SDLK_BACKSLASH: return BACKSLASH;
			case SDLK_EQUALS: return EQUALS;
			case SDLK_MINUS: return DASH;
			case SDLK_SPACE: return SPACE;
			case SDLK_RETURN: return ENTER;
			case SDLK_BACKSPACE: return BACKSPACE;
			case SDLK_TAB: return TAB;
			case SDLK_PAGEUP: return PAGEUP;
			case SDLK_PAGEDOWN: return PAGEDOWN;
			case SDLK_END: return END;
			case SDLK_HOME: return HOME;
			case SDLK_INSERT: return INS;
			case SDLK_DELETE: return DEL;
			case SDLK_KP_PLUS: return ADD;
			case SDLK_KP_MINUS: return SUBTRACT;
			case SDLK_KP_MULTIPLY: return MULTIPLY;
			case SDLK_KP_DIVIDE: return DIVIDE;
			case SDLK_LEFT: return LEFTARROW;
			case SDLK_RIGHT: return RIGHTARROW;
			case SDLK_UP: return UPARROW;
			case SDLK_DOWN: return DOWNARROW;
			case SDLK_KP_0: return NUMPAD_0;
			case SDLK_KP_1: return NUMPAD_1;
			case SDLK_KP_2: return NUMPAD_2;
			case SDLK_KP_3: return NUMPAD_3;
			case SDLK_KP_4: return NUMPAD_4;
			case SDLK_KP_5: return NUMPAD_5;
			case SDLK_KP_6: return NUMPAD_6;
			case SDLK_KP_7: return NUMPAD_7;
			case SDLK_KP_8: return NUMPAD_8;
			case SDLK_KP_9: return NUMPAD_9;
			case SDLK_F1: return F1;
			case SDLK_F2: return F2;
			case SDLK_F3: return F3;
			case SDLK_F4: return F4;
			case SDLK_F5: return F5;
			case SDLK_F6: return F6;
			case SDLK_F7: return F7;
			case SDLK_F8: return F8;
			case SDLK_F9: return F9;
			case SDLK_F10: return F10;
			case SDLK_F11: return F11;
			case SDLK_F12: return F12;
			case SDLK_F13: return F13;
			case SDLK_F14: return F14;
			case SDLK_F15: return F15;
			case SDLK_PAUSE: return PAUSE;
		}
		return 0;
	}
}