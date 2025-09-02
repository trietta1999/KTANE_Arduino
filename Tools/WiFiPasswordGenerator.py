import datetime
from jinja2 import Template

module_path_list = [
    "../../feature_Host_Timer/",
    "../../feature_Wires/",
    "../../feature_TheButton/",
    "../../feature_Keypads/",
    "../../feature_SimonSays/",
    "../../feature_WhosOnFirst/",
    "../../feature_Memory/",
    "../../feature_MorseCode/",
    "../../feature_ComplicatedWires/",
    "../../feature_Mazes/",
    "../../feature_Passwords/",
    "../../feature_needy_VentingGas/",
    "../../feature_needy_CapacitorDischarge/",
    "../../feature_needy_Knobs/",
    "../../feature_SystemInfo/",
]

wifi_conf_path = "ESP32/ssid_conf.h"

template_str = """
#define WIFI_SSID "{{ ssid }}"
#define WIFI_PASS "{{ password }}"
\n"""

template = Template(template_str)

rendered_text = template.render(
    ssid = "KTANE_Arduino",
    password = "KTANE_Arduino_" + datetime.datetime.now().strftime("%d%m%Y_%H%M%S")
)

for path in module_path_list:
    with open(path + wifi_conf_path, "w") as file:
        file.writelines(rendered_text)
