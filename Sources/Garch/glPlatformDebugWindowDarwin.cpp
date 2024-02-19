//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#if defined(__APPLE__)
/* -----------------------------------------------------------------
 * to reduce the need to explicitly exclude platform specific source
 * from SwiftPM, we will just guard the compilation by its platform,
 * thus we can prefer the ease of including all sources in the build
 * which is far more maintainable, especially for package consumers.
 * ----------------------------------------------------------------- */
#include "Garch/GarchDarwin/glPlatformDebugWindowDarwin.h"
#include "Garch/glDebugWindow.h"
#include <pxr/pxrns.h>

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <OpenGL/OpenGL.hpp>

PXR_NAMESPACE_USING_DIRECTIVE

#if 0
// XXX: FIXME: No-op. Probably just move this bit over to Swift.

static int
Garch_GetModifierKeys(NS::UInteger flags)
{
    int keys = 0;

    // The 10.12 SDK has new symbols.
#if MAC_OS_X_VERSION_MAX_ALLOWED < 101200
#define NSEventModifierFlagShift NSShiftKeyMask
#define NSEventModifierFlagControl NSControlKeyMask
#define NSEventModifierFlagOption NSAlternateKeyMask
#define NSEventModifierFlagCommand NSCommandKeyMask
#endif
    if (flags & NS::EventModifierFlagShift)   keys |= GarchGLDebugWindow::Shift;
    if (flags & NS::EventModifierFlagControl) keys |= GarchGLDebugWindow::Ctrl;
    if (flags & NS::EventModifierFlagOption)  keys |= GarchGLDebugWindow::Alt;
    if (flags & NS::EventModifierFlagCommand) keys |= GarchGLDebugWindow::Alt;

    return keys;
}

class Garch_GLPlatformView : NS::Object/*NSGL::OpenGLView <NSWindowDelegate>*/
{
    GarchGLDebugWindow *_callback;
    NSGL::OpenGLContext *_ctx;

    Garch_GLPlatformView* initGL(NSGL::Rect frame,  GarchGLDebugWindow *cb)
    {
        _callback = cb;

        int attribs[] = {
            NSGL::OpenGLPFAAccelerated,
            NSGL::OpenGLPFADoubleBuffer,
            NSGL::OpenGLPFADepthSize, 24,
            NSGL::OpenGLPFAAlphaSize, 8,
            NSGL::OpenGLPFAColorSize, 32,
            NSGL::OpenGLPFANoRecovery,
            NSGL::OpenGLPFAOpenGLProfile, 
            NSGL::OpenGLProfileVersion3_2Core,
            0
        };

        NSGL::OpenGLPixelFormat *pf = NSGL::OpenGLPixelFormat::alloc()->init((NSGL::OpenGLPixelFormatAttribute*)attribs);

        //this->init(/*frame.pixelFormat(pf)*/);

        _ctx = NSGL::OpenGLContext::alloc()->init(pf, nil);

        //this->setOpenGLContext(_ctx);

        _ctx->makeCurrentContext();

        _callback->OnInitializeGL();

        pf->release();

        return this;
    }

    bool acceptsFirstResponder()
    {
        return true;
    }

    void drawRect(NSGL::Rect theRect)
    {
        _ctx->makeCurrentContext();

        _callback->OnPaintGL();

        this->openGLContext()->flushBuffer();
    }

    void windowWillClose(NS::Notification *notification)
    {
        NS::Application::sharedApplication()->terminate(this);
    }

    void windowDidResize(NS::Notification *notification)
    {
        NSGL::Rect r = this->frame();
        _callback->OnResize(r.size.width, r.size.height);
    }

    void mouseDown(NSEvent *event)
    {
        NSGL::Point p = event->locationInWindow();
        NSGL::Rect r = self->frame();
        NS::UInteger modflags = event->modifierFlags();
        _callback->OnMousePress(GarchGLDebugWindow::MyButton1,
                                p.x, r.size.height - 1 - p.y,
                                Garch_GetModifierKeys(modflags));

        this->setNeedsDisplay(true);
    }

    void mouseUp(NSEvent *event)
    {
        NSGL::Point p = event->locationInWindow();
        NSGL::Rect r = this->frame();
        NS::UInteger modflags = event->modifierFlags();
        _callback->OnMouseRelease(GarchGLDebugWindow::MyButton1,
                                  p.x, r.size.height - 1 - p.y,
                                  Garch_GetModifierKeys(modflags));

        this->setNeedsDisplay(true);
    }

    void mouseDragged(NSEvent *event)
    {
        NSGL::Point p = event->locationInWindow();
        NSGL::Rect r = this->frame();
        NS::UInteger modflags = event->modifierFlags();
        _callback->OnMouseMove(p.x, r.size.height - 1 - p.y,
                              Garch_GetModifierKeys(modflags));

        this->setNeedsDisplay(true);
    }

    void keyDown(NS::Event *event)
    {
        int keyCode = event->keyCode();
        int key = 0;

        // XXX shoud call UCKeyTranslate() for non-us keyboard
        const int keyMap[] = { 0x00, 'a', 0x0b, 'b', 0x08, 'c', 0x02, 'd',
                              0x0e, 'e', 0x03, 'f', 0x05, 'g', 0x04, 'h',
                              0x22, 'i', 0x26, 'j', 0x28, 'k', 0x25, 'l',
                              0x2e, 'm', 0x2d, 'n', 0x1f, 'o', 0x23, 'p',
                              0x0c, 'q', 0x0f, 'r', 0x01, 's', 0x11, 't',
                              0x20, 'u', 0x09, 'v', 0x0d, 'w', 0x07, 'x',
                              0x10, 'y', 0x06, 'z', 0x31, ' ', -1, -1};

        for (int i = 0; keyMap[i] >=0; i += 2) {
            if (keyMap[i] == keyCode) {
                key = keyMap[i+1];
                break;
            }
        }
        if (key) {
            _callback->OnKeyRelease(key);
        }

        this->setNeedsDisplay(true);
    }
};

// ---------------------------------------------------------------------------

#endif // 0

PXR_NAMESPACE_OPEN_SCOPE

Garch_GLPlatformDebugWindow::Garch_GLPlatformDebugWindow(GarchGLDebugWindow *w)
    : _callback(w) {}

void Garch_GLPlatformDebugWindow::Init(const char *title, int width, int height,
                                       int nSamples)
{
#if 0
    // XXX: FIXME: No-op. Probably just move this bit over to Swift.

    NS::Application::sharedApplication();
    NS::App::setActivationPolicy(NS::ApplicationActivationPolicyRegular);
    id applicationName = NS::ProcessInfo::processInfo()->processName();

    NSGL::Rect frame = NSGL::Rect::Make(0, 0, width, height);
    NSGL::Rect viewBounds = NSGL::Rect::Make(0, 0, width, height);

    Garch_GLPlatformView *view = Garch_GLPlatformView::alloc()->initGL(viewBounds, _callback);

    NS::Window *window = NS::Window::alloc()->init(frame,
                                                   NS::TitledWindowMask
                                                 | NS::ClosableWindowMask
                                                 | NS::MiniaturizableWindowMask
                                                 | NS::ResizableWindowMask,
                                                   NS::BackingStoreBuffered,
                                                   false);
    window->setCascadeTopLeftFromPoint(NSMakePoint(20,20));
    window->setTitle(applicationName);
    window->makeKeyAndOrderFront(nil);

    NS::App::activateIgnoringOtherApps(true);

    window->setContentView(view);
    window->setDelegate(view);
#endif // 0
}

void Garch_GLPlatformDebugWindow::Run()
{
#if 0
    // XXX: FIXME: No-op. Probably just move this bit over to Swift.

    NS::App::run();
#endif // 0
}

void Garch_GLPlatformDebugWindow::ExitApp()
{
#if 0
    // XXX: FIXME: No-op. Probably just move this bit over to Swift.

    NS::App::stop(nil);
#endif // 0
}

PXR_NAMESPACE_CLOSE_SCOPE

#endif /* defined(__APPLE__) */
