#include<obs-module.h>

struct webrtc_millicast {
    char *server, *milli_id, *codec;
};

static const char *webrtc_millicast_name(void *unused)
{
	UNUSED_PARAMETER(unused);
	return obs_module_text("WebRTC Millicast Streaming Server");
}

static void webrtc_millicast_update(void *data, obs_data_t *settings)
{
	struct webrtc_millicast *service = data;

	bfree(service->server);
	bfree(service->milli_id);
	bfree(service->codec);

	service->server = bstrdup(obs_data_get_string(settings, "server"));
	service->milli_id = bstrdup(obs_data_get_string(settings, "milli_id"));
	service->codec = bstrdup(obs_data_get_string(settings, "codec"));
}

static void webrtc_millicast_destroy(void *data)
{
	struct webrtc_millicast *service = data;

	bfree(service->server);
	bfree(service->milli_id);
	bfree(service->codec);
	bfree(service);
}

static void *webrtc_millicast_create(obs_data_t *settings, obs_service_t *service)
{
	struct webrtc_millicast *data = bzalloc(sizeof(struct webrtc_millicast));
	webrtc_millicast_update(data, settings);

	UNUSED_PARAMETER(service);
	return data;
}

static obs_properties_t *webrtc_millicast_properties(void *unused)
{
	UNUSED_PARAMETER(unused);

	obs_properties_t *ppts = obs_properties_create();

	obs_properties_add_text(ppts, "server", "Web Server URL", OBS_TEXT_DEFAULT);
	obs_properties_add_text(ppts, "milli_id", "ID", OBS_TEXT_DEFAULT);
	obs_properties_add_text(ppts, "codec", "Video codec", OBS_TEXT_DEFAULT);

	return ppts;
}

static const char *webrtc_millicast_url(void *data)
{
	struct webrtc_millicast *service = data;
	return service->server;
}

static const char *webrtc_millicast_id(void *data)
{
	struct webrtc_millicast *service = data;
	return service->milli_id;
}

static const char *webrtc_millicast_codec(void *data)
{
	struct webrtc_millicast *service = data;
	return service->codec;
}

struct obs_service_info webrtc_millicast_service = {
	.id             = "webrtc_millicast",
	.get_name       = webrtc_millicast_name,
	.create         = webrtc_millicast_create,
	.destroy        = webrtc_millicast_destroy,
	.update         = webrtc_millicast_update,
	.get_properties = webrtc_millicast_properties,
	.get_url        = webrtc_millicast_url,
	.get_milli_id   = webrtc_millicast_id,
	.get_codec      = webrtc_millicast_codec
};