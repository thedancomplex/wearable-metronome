#ifndef __metronome_H__
#define __metronome_H__

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "metronome"

#if !defined(PACKAGE)
#define PACKAGE "com.lofarolabs.metronome"
#endif

#endif /* __metronome_H__ */

void changeText(double bpm);


