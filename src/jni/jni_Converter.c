/* JNativeHook: Global keyboard and mouse hooking for Java.
 * Copyright (C) 2006-2013 Alexander Barker.  All Rights Received.
 * http://code.google.com/p/jnativehook/
 *
 * JNativeHook is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * JNativeHook is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <jni.h>
#include <nativehook.h>

#include "jni_Converter.h"
#include "org_jnativehook_NativeInputEvent.h"
#include "org_jnativehook_keyboard_NativeKeyEvent.h"
#include "org_jnativehook_mouse_NativeMouseEvent.h"
#include "org_jnativehook_mouse_NativeMouseWheelEvent.h"


jint jni_ConvertToJavaType(EventType nativeType, jint *javaType) {
	jint status = JNI_OK;

	switch (nativeType) {
		case EVENT_KEY_PRESSED:
			*javaType = org_jnativehook_keyboard_NativeKeyEvent_NATIVE_KEY_PRESSED;
			break;

		case EVENT_KEY_RELEASED:
			*javaType = org_jnativehook_keyboard_NativeKeyEvent_NATIVE_KEY_RELEASED;
			break;

		case EVENT_KEY_TYPED:
			*javaType = org_jnativehook_keyboard_NativeKeyEvent_NATIVE_KEY_TYPED;
			break;

		case EVENT_MOUSE_PRESSED:
			*javaType = org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_PRESSED;
			break;

		case EVENT_MOUSE_RELEASED:
			*javaType = org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_RELEASED;
			break;

		case EVENT_MOUSE_CLICKED:
			*javaType = org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_CLICKED;
			break;

		case EVENT_MOUSE_MOVED:
			*javaType = org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_MOVED;
			break;

		case EVENT_MOUSE_DRAGGED:
			*javaType = org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_DRAGGED;
			break;

		case EVENT_MOUSE_WHEEL:
			*javaType = org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_WHEEL;
			break;

		default:
			*javaType = 0;
			status = JNI_ERR;
			break;
	}

	return status;
}


jint jni_ConvertToNativeType(jint javaType, EventType *nativeType) {
	jint status = JNI_OK;

	switch (javaType) {
		case org_jnativehook_keyboard_NativeKeyEvent_NATIVE_KEY_PRESSED:
			*nativeType = EVENT_KEY_PRESSED;
			break;

		case org_jnativehook_keyboard_NativeKeyEvent_NATIVE_KEY_RELEASED:
			*nativeType = EVENT_KEY_RELEASED;
			break;

		case org_jnativehook_keyboard_NativeKeyEvent_NATIVE_KEY_TYPED:
			*nativeType = EVENT_KEY_TYPED;
			break;

		case org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_PRESSED:
			*nativeType = EVENT_MOUSE_PRESSED;
			break;

		case org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_RELEASED:
			*nativeType = EVENT_MOUSE_RELEASED;
			break;

		case org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_CLICKED:
			*nativeType = EVENT_MOUSE_CLICKED;
			break;

		case org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_MOVED:
			*nativeType = EVENT_MOUSE_MOVED;

		case org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_DRAGGED:
			*nativeType = EVENT_MOUSE_DRAGGED;

		case org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_WHEEL:
			*nativeType = EVENT_MOUSE_WHEEL;
			break;

		default:
			*nativeType = 0;
			status = JNI_ERR;
			break;
	}

	return status;
}


jint jni_ConvertToNativeKeyCode(jint javaKeyCode, jint javaKeyLocation, unsigned short *nativeKeyCode) {
	jint status = JNI_OK;

	switch (javaKeyLocation) {
		case org_jnativehook_keyboard_NativeKeyEvent_LOCATION_LEFT:
		case org_jnativehook_keyboard_NativeKeyEvent_LOCATION_RIGHT:
				*nativeKeyCode = (javaKeyCode >> 2) & 0x02FF;
			break;

		case org_jnativehook_keyboard_NativeKeyEvent_LOCATION_NUMPAD:
			*nativeKeyCode = (javaKeyCode >> 2) & 0x01FF;
			break;

		default:
		case org_jnativehook_keyboard_NativeKeyEvent_LOCATION_STANDARD:
			// No conversion required.
			*nativeKeyCode = javaKeyCode;
			break;
	}

	return status;
}


jint jni_ConvertToJavaKeyCode(unsigned short int nativeKeyCode, jint *javaKeyCode, jint *javaKeyLocation) {
	jint status = JNI_OK;

	switch (nativeKeyCode) {
		case VC_SHIFT_L:
		case VC_CONTROL_L:
		case VC_ALT_L:
		case VC_META_L:
			*javaKeyCode = nativeKeyCode;
			*javaKeyLocation = org_jnativehook_keyboard_NativeKeyEvent_LOCATION_LEFT;
			break;

		case VC_SHIFT_R:
		case VC_CONTROL_R:
		case VC_ALT_R:
		case VC_META_R:
			*javaKeyCode = nativeKeyCode & 0xFF;
			*javaKeyLocation = org_jnativehook_keyboard_NativeKeyEvent_LOCATION_RIGHT;
			break;

		case VC_KP_0:
		case VC_KP_1:
		case VC_KP_2:
		case VC_KP_3:
		case VC_KP_4:
		case VC_KP_5:
		case VC_KP_6:
		case VC_KP_7:
		case VC_KP_8:
		case VC_KP_9:

		case VC_KP_ENTER:
		case VC_KP_MULTIPLY:
		case VC_KP_ADD:
		case VC_KP_SEPARATOR:
		case VC_KP_SUBTRACT:
		case VC_KP_DIVIDE:
			*javaKeyCode = nativeKeyCode & 0xFF;
			*javaKeyLocation = org_jnativehook_keyboard_NativeKeyEvent_LOCATION_NUMPAD;
			break;

		default:
			*javaKeyCode = nativeKeyCode;
			*javaKeyLocation = org_jnativehook_keyboard_NativeKeyEvent_LOCATION_STANDARD;
			break;
	}

	return status;
}

/*
jint jni_ConvertToJavaModifierMask(unsigned int nativeMask, jint *javaMask) {
	jint status = JNI_OK;

	*javaMask = (jint) nativeMask;

	return status;
}


jint jni_ConvertToNativeModifierMask(jint javaType, unsigned int *nativeType) {
	jint status = JNI_OK;

	*nativeType = (unsigned int) javaType;

	return status;
}
*/
