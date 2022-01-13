#include "AssWriter.h"

string scriptInfo = "[Script Info]\n; This is an Advanced Sub Station Alpha v4+ script.\nTitle: subtitles\nScriptType: v4.00+\nCollisions: Normal\nPlayDepth: 0\n\n";
string styles = "[V4+ Styles]\nFormat: Name, Fontname, Fontsize, PrimaryColour, SecondaryColour, OutlineColour, BackColour, Bold, Italic, Underline, StrikeOut, ScaleX, ScaleY, Spacing, Angle, BorderStyle, Outline, Shadow, Alignment, MarginL, MarginR, MarginV, Encoding\n";
string style = "%s,%s,%d,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n";
//Style : Chinese, 方正黑體_GBK, 21, & H00FFFFFF, & HF0000000, & H006C3300, & H00000000, -1, 0, 0, 0, 100, 100, 0, 0, 1, 2, 1, 8, 5, 5, 1, 134
//Style : English, Arial, 20, & H00FFFFFF, & H0300FFFF, & H00000000, & H02000000, 0, 0, 0, 0, 100, 100, 0, 0, 1, 2, 1, 2, 10, 10, 10, 1
string events = "\n[Events]\nFormat: Layer, Start, End, Style, Actor, MarginL, MarginR, MarginV, Effect, Text\n";

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

AssWriter::AssWriter()
{
}

void AssWriter::write(const char *assFileName, list<SrtSubtitle>& srtSubtitles)
{
    FILE* assfp;
    errno_t err;
    if ((err = fopen_s(&assfp, assFileName, "w")) == 0 && assfp != 0)
    {
        fprintf(assfp, &scriptInfo[0]);
        fprintf(assfp, &styles[0]);

        list<SrtSubtitle> srtSubs;
        while (!srtSubtitles.empty()) {
            SrtSubtitle srtSubtitle = srtSubtitles.front();
            string language = srtSubtitle.language;
            if (language.compare("English") == 0 || language.compare("english") == 0) {
                fprintf(assfp, "Style: %s,Arial,20,&H00FFFFFF,&H0300FFFF,&H00000000,&H02000000,0,0,0,0,100,100,0,0,1,2,1,2,10,10,10,1\n", language.c_str());
            }
            else {
                fprintf(assfp, "Style: %s,方正黑體_GBK,21,&H00FFFFFF,&HF0000000,&H006C3300,&H00000000,-1,0,0,0,100,100,0,0,1,2,1,8,5,5,1,134\n", language.c_str());
            }
            srtSubtitles.pop_front();
            srtSubs.push_back(srtSubtitle);
        }

        fprintf(assfp, &events[0]);

        while (!srtSubs.empty()) {
            SrtSubtitle srtSubtitle = srtSubs.front();
            while (!srtSubtitle.subtitles.empty()) {
                SrtSubtitleLine srtSubtitleLine = srtSubtitle.subtitles.front();
                SrtTime startTime = srtSubtitleLine.startTime;
                SrtTime endTime = srtSubtitleLine.endTime;

                startTime.milliSecond = startTime.milliSecond / 10;
                endTime.milliSecond = endTime.milliSecond / 10;

                //Dialogue: 0,0:00:59.24,0:01:02.12,Default,,0,0,0,,<i>Where I grew up,\NLouisiana, Cedar Grove,</i>
                fprintf(assfp,"Dialogue: 0,%d:%02d:%02d.%02d,%d:%02d:%02d.%02d,%s,,0,0,0,,",startTime.hour,startTime.minute,startTime.second,startTime.milliSecond,endTime.hour,endTime.minute,endTime.second,endTime.milliSecond,srtSubtitle.language.c_str());

                while (!srtSubtitleLine.lines.empty()) {
                    string line = srtSubtitleLine.lines.front();
                    replaceAll(line, "<i>", "{\\i1}");
                    replaceAll(line, "</i>", "{\\i0}");
                    fprintf(assfp, "%s", line.c_str());
                    srtSubtitleLine.lines.pop_front();
                    if (!srtSubtitleLine.lines.empty()) {
                        fprintf(assfp, "\\N");
                    }
                }
                srtSubtitle.subtitles.pop_front();

                if (!srtSubtitle.subtitles.empty()) {
                    fprintf(assfp, "\n");
                }
            }

            srtSubs.pop_front();
        }
        fclose(assfp);
    }
}
