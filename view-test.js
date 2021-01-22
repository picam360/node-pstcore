var pstcore = require('./index.js');

var config_json = "";
config_json += "{\n";
config_json += "	\"plugin_paths\" : [\n";
config_json += "		\"plugins/pvf_loader_st.so\",\n";
config_json += "		\"plugins/libde265_decoder_st.so\",\n";
config_json += "		\"plugins/vt_decoder_st.so\",\n";
config_json += "		\"plugins/pgl_renderer_st.so\"\n";
config_json += "	]\n";
config_json += "}\n";
pstcore.pstcore_init(config_json);

pstcore.pstcore_add_set_param_done_callback(
(msg)=>{
	console.log("set_param " + msg);
});

var url = "http://vpm.picam360.com/heli-ki60_2160p.pvf";

var def = "pvf_loader ! libde265_decoder name=decoder ! pgl_renderer name=renderer format=p2s w=640 h=480 fps=30";
pst = pstcore.pstcore_build_pstreamer(def);
pstcore.pstcore_set_param(pst, "pvf_loader", "url", url);
//pstcore.pstcore_set_param(pst, "renderer", "win_titlebar", "0");
pstcore.pstcore_start_pstreamer(pst);

setInterval(() => {
	var pps = pstcore.pstcore_get_param(pst, "decoder", "pixelrate_mpps");
	console.log("pps=" + pps);
}, 1000);

setInterval(() => {
	pstcore.pstcore_poll_events();
}, 33);
