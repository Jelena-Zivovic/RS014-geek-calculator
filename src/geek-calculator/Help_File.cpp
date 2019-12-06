#include "Help_File.hpp"


Help_File::Help_File() {
    m_file.open(filename, std::ofstream::out);
    m_file_star = fopen(filename, "r");
}

Help_File::~Help_File() {
    m_file.close();
    fclose(m_file_star);
}

void Help_File::write(const QString& text) {
    m_file << text.toStdString() << std::endl;
}

FILE* Help_File::get_FILE() const {
    return m_file_star;
}
