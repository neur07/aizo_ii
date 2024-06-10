#include "FileLoader.h"
#include <fstream>

using namespace std;

FileLoader::FileLoader(string basePath) : base_path(basePath) {}

IMGraph* FileLoader::read_im(string fileName) {
    size_t edgeCount, vertexCount;
    size_t* data;

    if (!load_data(fileName, edgeCount, vertexCount, data)) {
        return nullptr;
    }

    IMGraph* matrix = new IMGraph(edgeCount, vertexCount, data);

    delete[] data;

    return matrix;
}

ALGraph* FileLoader::read_al(string fileName) {
    size_t edgeCount, vertexCount;
    size_t* data;

    if (!load_data(fileName, edgeCount, vertexCount, data)) {
        return nullptr;
    }

    ALGraph* list = new ALGraph(edgeCount, vertexCount, data);

    delete[] data;

    return list;
}

bool FileLoader::load_data(string fileName, size_t& edgeCount, size_t& vertexCount, size_t*& data) {
    ifstream file(base_path + fileName);

    if (file.fail()) {
        return false;
    }

    file >> edgeCount >> vertexCount;

    size_t dataSize = edgeCount * 3;
    data = new size_t[dataSize];

    for (size_t i = 0; i < dataSize; ++i) {
        file >> data[i];
    }

    return true;
}
