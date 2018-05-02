// OBS-OST.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "RTSSWrapper.h"
#include "OBSLogger.h"

#include <obs-module.h>
#include <obs-frontend-api/obs-frontend-api.h>

OBS_DECLARE_MODULE()
// OBS_MODULE_USE_DEFAULT_LOCALE("my-plugin", "en-US")

RTSSWrapper* rtss;
OBSLogger obslog = OBSLogger("[OBS-OSD]");

void obs_osd_frontend_event_callback(enum obs_frontend_event event, void *private_data) {
	switch (event) {
	case OBS_FRONTEND_EVENT_STREAMING_STARTING:
		obslog.Info("Streaming Starting");
		break;
	case OBS_FRONTEND_EVENT_STREAMING_STARTED:
		obslog.Info("Streaming Started");
		rtss->showStreaming();
		break;
	case OBS_FRONTEND_EVENT_STREAMING_STOPPING:
		obslog.Info("Streaming Stopping");
		break;
	case OBS_FRONTEND_EVENT_STREAMING_STOPPED:
		obslog.Info("Streaming Stopped");
		rtss->hide();
		break;
	case OBS_FRONTEND_EVENT_RECORDING_STARTING:
		obslog.Info("Recording Starting");
		break;
	case OBS_FRONTEND_EVENT_RECORDING_STARTED:
		obslog.Info("Recording Started");
		rtss->showRecording();
		break;
	case OBS_FRONTEND_EVENT_RECORDING_STOPPING:
		obslog.Info("Recording Stopping");
		break;
	case OBS_FRONTEND_EVENT_RECORDING_STOPPED:
		obslog.Info("Recording Stopped");
		rtss->hide();
		break;
	case OBS_FRONTEND_EVENT_EXIT:
		obslog.Info("Exiting");
		rtss->hide();
		break;
	}
}

bool obs_module_load(void) {
	obs_frontend_add_event_callback(obs_osd_frontend_event_callback, 0);
	obslog.Info("Loaded");
	return true;
}

void obs_module_unload() {

}

const char *obs_module_author(void) {
	return "Rave";
}

const char *obs_module_name(void) {
	return "OBS-OSD";
}

const char *obs_module_description(void) {
	return "OSD for OBS using RTSS";
}