#include <iostream>
#include <thread>
#include <string>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <vector>

namespace
{
std::string print_help()
{
    return "bin2array [--help] input_file [output_file]\n";
}
std::string tolower(std::string_view data)
{
    std::string result{data};

    std::transform(
        data.begin(), data.end(), result.begin(),
        [](std::string_view::value_type const c) {
            return static_cast<std::string::value_type>(std::tolower(c));
        });

    return result;
}
}  // namespace

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Error: You need to pass at least one parameter.\n";
        std::cout << print_help();
        return 2;
    }

    if (tolower(argv[1U]) == "--help")
    {
        std::cout << print_help();
        return 1;
    }

    // Input file is mandatory input parameter.
    std::string input_file{argv[1U]};
    // Output file is optional second parameter.
    std::string output_file{argc > 2 ? argv[2U] : input_file + ".out"};

    {
        // Open file
        std::ifstream input(input_file, std::ios::binary);
        if (!input)
        {
            std::cerr << "Cannot open file: " << input_file << std::endl;
            return 3;
        }

        std::ofstream output("C:\\myfile.gif", std::ios::binary);
        if (!output)
        {
            std::cerr << "Cannot open output file: " << output_file
                      << std::endl;
            return 4;
        }

        // Now we have both files open. It is time to start the proccess.

        // First write header of file.
        output << "unsigned char data[] = {\n";

        // copies all data into buffer
        std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input),
                                          {});
        auto const last = buffer.back();
        buffer.pop_back();

        for (auto const element : buffer)
        {
            output << std::to_string(static_cast<unsigned int>(element)) << ",";
        }
        output << std::to_string(static_cast<unsigned int>(last));
        output << "\n};";
    }

    std::cout << "File converted successfully" << std::endl;

    return 0;
}
