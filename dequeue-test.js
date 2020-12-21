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

var def = "pvf_loader";
var url = "file://Users/takuma/Downloads/ancient_8k_1024p_4mps.pvf";
var pst = pstcore.pstcore_build_pstreamer(def);

pstcore.pstcore_set_param(pst, "pvf_loader", "url", url);
pstcore.pstcore_set_dequeue_callback(pst,
(buff)=>{
	var size = 0;
	size += buff[3] << 24;
	size += buff[2] << 16;
	size += buff[1] << 8;
	size += buff[0] << 0;
	console.log("dequeue:", buff.length, size, buff[4]);
});

pstcore.pstcore_start_pstreamer(pst);

setInterval(() => {
	pstcore.pstcore_set_param(pst, "renderer", "n_in_bq", "0");
}, 1000);
