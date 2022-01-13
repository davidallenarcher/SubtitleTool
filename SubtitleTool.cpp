#include <string>
#include <list>
#include "AssWriter.h"
#include "SrtReader.h"
#include "SrtSubtitle.h"
using namespace std;

int main(int argc, char* argv[]) {
    SrtReader* srtReader = new SrtReader();
    AssWriter* assWriter = new AssWriter();

    list<SrtSubtitle> srtSubtitles;

    for (int i = 1; i < argc; i++) {
        SrtSubtitle srtSubtitle;
        srtReader->read(argv[i], srtSubtitle.subtitles);
        char language[64];

        printf("SRT file [%d]: \"%s\"\n", i, argv[i]);
        printf("Language: ");
        scanf_s("%63s", language, 64);
        printf("Selected Language: %s\n", language);

        srtSubtitle.language = language;

        srtSubtitles.push_back(srtSubtitle);
    }

    assWriter->write("subtitle.ass", srtSubtitles);
}

/*
int main() {
    if (regex_match("softwareTesting", regex("(soft)(.*)")))
        cout << "string:literal => matched\n";

    const char mystr[] = "SoftwareTestingHelp";
    string str("software");
    regex str_expr("(soft)(.*)");

    if (regex_match(str, str_expr))
        cout << "string:object => matched\n";

    if (regex_match(str.begin(), str.end(), str_expr))
        cout << "string:range(begin-end)=> matched\n";

    cmatch cm;
    regex_match(mystr, cm, str_expr);

    smatch sm;
    regex_match(str, sm, str_expr);

    regex_match(str.cbegin(), str.cend(), sm, str_expr);
    cout << "String:range, size:" << sm.size() << " matches\n";


    regex_match(mystr, cm, str_expr, regex_constants::match_default);

    cout << "the matches are: ";
    for (unsigned i = 0; i < sm.size(); ++i) {
        cout << "[" << sm[i] << "] ";
    }

    cout << endl;

    return 0;
}
*/


/*
int readSrtFile(char* srtFileName, char*& srtFileContent)
{
    FILE* srtfp;
    errno_t err;
    if ((err = fopen_s(&srtfp, srtFileName, "rb")) == 0 && srtfp != 0)
    {
        fseek(srtfp, 0, SEEK_END);
        long fsize = ftell(srtfp);
        fseek(srtfp, 0, SEEK_SET);

        srtFileContent = (char*)malloc(fsize + 1);
        fread(srtFileContent, fsize, 1, srtfp);
        fclose(srtfp);
    }

    return err;
}

int main(int argc, char** argv)
{
    FILE* fp;
    errno_t err;

    if (argc < 3) {
        printf("Drag \"*.srt\" files onto SubtitleTool.exe");
        return 0;
    }

    printf("argc:%d\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d]:%s\n", i, argv[i]);
    }

    char* file1Contents;
    if (readSrtFile(argv[1], file1Contents) != 0)
    {
        printf("Could not read file: %s", argv[1]);
        return 0;
    }

    const char* fileName = "test.txt";
    if ((err = fopen_s(&fp, fileName, "w")) == 0 && fp != 0)
    {
        fprintf(fp, "argc:%d\n", argc);
        for (int i = 0; i < argc; i++)
        {
            fprintf(fp, "argv[%d]:%s\n", i, argv[i]);
        }
        fprintf(fp, "%s", file1Contents);
    }
}
*/

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu