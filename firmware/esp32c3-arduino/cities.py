import requests
import csv

# Looks like ESP-IDF pulls in whole POSIX stack
# Some forums mention ESP-IDF uses this CSV

coords = {}

r = requests.get("https://gist.githubusercontent.com/erdem/8c7d26765831d0f9a8c62f02782ae00d/raw/248037cd701af0a4957cce340dabb0fd04e38f4c/countries.json")
data = r.json()
for j in data:
    for tz in j["timezones"]:
        coords[tz] = j["latlng"]


r = requests.get("https://raw.githubusercontent.com/nayarsystems/posix_tz_db/master/zones.csv")
cr = csv.reader(r.text.splitlines(), delimiter=',', quotechar='"')

print("""const char cities[] = R"(
<br/>
<label for="city">Nearest city</label>
<select name="city" id="city" onchange="
document.getElementById('timezone').value = this.value;
document.getElementById('long').value = this.options[this.selectedIndex].dataset.long;
document.getElementById('lat').value = this.options[this.selectedIndex].dataset.lat;
">""")
for name, code in cr:
    if name.startswith("Etc/"):
        continue
    if not name.startswith("Europe/"):
        continue
    longlat = coords.get(name)
    selected = name == "Europe/Tallinn"
    print("""<option value="%s" data-long="%s" data-lat="%s"%s>%s</option>""" % (
        code,
        int(longlat[0]) if longlat else "",
        int(longlat[1]) if longlat else "",
        " selected" if selected else "",
        name))
print("""</select>
)";
""")
