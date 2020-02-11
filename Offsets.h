/// Definitions of various sets of offsets used by the games

#ifndef Offsets_h
#define Offsets_h

#include "CppTypes.h"
#include <type_traits>
#include <OpenGL/gl.h>

/// Indicates that the value will not be used by the program for the given game
/// Set to a value that will most likely cause a crash if it does get used (since these are used as offsets, 0 will not cause a direct crash)
static const size_t UNUSED_VALUE = 1UL << 48;

struct AnyMemberOffset {
	size_t offset;
	inline explicit AnyMemberOffset(size_t _offset): offset(_offset) {}
};
struct AnyVtableOffset {
	size_t offset;
	inline explicit AnyVtableOffset(size_t _offset): offset(_offset) {}
};

/// An offset from a class to an instance variable in that class
template<typename C, typename M>
struct MemberOffset {
	using Class = C;
	using Member = M;
	size_t offset = UNUSED_VALUE;

	MemberOffset() = default;
	inline /*implicit*/ MemberOffset(AnyMemberOffset off): offset(off.offset) {}

	Member& apply(Class* c) const {
		return *(Member*)(reinterpret_cast<unsigned char *>(c) + offset);
	}
};

/// An offset from a class's vtable to a particular method in that vtable
template<typename C, typename R, typename... Args>
struct VtableOffset {
	using Result = R;
	using Class = C;
	using Function = Result(*)(Class*, Args...);
	size_t offset = UNUSED_VALUE;

	VtableOffset() = default;
	inline /*implicit*/ VtableOffset(AnyVtableOffset off): offset(off.offset) {}

	Result operator()(Class* c, Args... args) const {
		return bind(c)(c, args...);
	}

	Function bind(Class* c) const {
		unsigned char *vtable = *reinterpret_cast<unsigned char **>(c);
		return *reinterpret_cast<Function*>(vtable + offset);
	}
};

extern struct ScreenManagerOffsets {
	VtableOffset<ScreenManager, void, int, int, bool, int> RequestResolution;
	VtableOffset<ScreenManager, int> GetHeight;
	VtableOffset<ScreenManager, int> IsFullscreen;
	VtableOffset<ScreenManager, int> ReleaseMode;
	MemberOffset<ScreenManager, void*> window;
	MemberOffset<ScreenManager, void*> playerWindowView;
	MemberOffset<ScreenManager, void*> playerWindowDelegate;
	MemberOffset<ScreenManager, bool> isFullscreen;
	MemberOffset<ScreenManager, int> width;
	MemberOffset<ScreenManager, int> height;
	MemberOffset<ScreenManager, GLuint> framebufferA;
	MemberOffset<ScreenManager, GLuint> framebufferB;
	MemberOffset<ScreenManager, RenderSurface*> renderSurfaceA;
	MemberOffset<ScreenManager, RenderSurface*> renderSurfaceB;
} screenMgrOffsets;

extern struct GfxDeviceOffsets {
	VtableOffset<GfxDevice, void> FinishRendering;
	VtableOffset<GfxDevice, void, RenderSurface*, RenderSurface*> SetBackBufferColorDepthSurface;
	VtableOffset<GfxDevice, void, Matrix4x4f*> SetProjectionMatrix;
	VtableOffset<GfxDevice, void, Matrix4x4f*> SetViewMatrix;
	VtableOffset<GfxDevice, void, RectTInt*> SetViewport;
	VtableOffset<GfxDevice, void, RenderSurface*> DeallocRenderSurface;
} gfxDevOffsets;

extern struct PlayerSettingsOffsets {
	MemberOffset<PlayerSettings, bool> collectionBehaviorFlag;
} playerSettingsOffsets;

extern struct QualitySettingsOffsets {
	MemberOffset<QualitySettings, QualitySetting*> settingsVector;
	MemberOffset<QualitySettings, int> currentQuality;
} qualitySettingsOffsets;

extern struct QualitySettingOffsets {
	MemberOffset<QualitySetting, int> vSyncCount;
	size_t size = UNUSED_VALUE;
} qualitySettingOffsets;

extern struct InputManagerOffsets {
	MemberOffset<InputManager, Pointf> mousePosition;
} inputMgrOffsets;

#endif /* Offsets_h */
