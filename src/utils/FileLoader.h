#include <string>
#include <IMGraph.h>
#include <ALGraph.h>

using namespace std;

class FileLoader {
public:
    FileLoader(string base_path);

    IMGraph* read_im(string file_name);
    ALGraph* read_al(string file_name);

private:
    bool load_data(string file_name, size_t& edge_count, size_t& vertex_count, size_t*& data);

    string base_path;
};
