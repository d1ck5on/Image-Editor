#include <iostream>
#include <Image.h>
#include <limits>

#include <SharpeningFilter.h>
#include <CropFilter.h>
#include <GrayscaleFilter.h>
#include <NegativeFilter.h>
#include <EdgeDetectionFilter.h>

#include <BMP.h>
#include <smplcli/program_parameters.h>

void ApplySubprogram(smplcli::ProgramParameters& subprog, Image& image);

int main(int argc, char* argv[]) {
    using ParamType = smplcli::Parameter::ParameterType;

    smplcli::ProgramParameters program("Image Editor");
    program.Description(
        "Image processing using various filters. \n\t24bit BMP without compression and color table only.");

    program.AddParameter<std::string>(ParamType::Argument, "input_file").Help("Path to the input file in BMP format");
    program.AddParameter<std::string>(ParamType::Argument, "output_file").Help("Path to the output file in BMP format");
    ;

    auto& crop = program.AddSubprog("-crop");
    crop.Description("Crops the image to the specified width and height. The upper left part of the image is used.");
    crop.AddParameter<int>(ParamType::Argument, "width");
    crop.AddParameter<int>(ParamType::Argument, "height");

    program.AddSubprog("-gs").Description("Converts the image to grayscale.");

    program.AddSubprog("-neg").Description("Converts the image to negative.");

    program.AddSubprog("-sharp").Description("Sharpening.");

    auto& edge_detection = program.AddSubprog("-edge");
    edge_detection.AddParameter<float>(ParamType::Argument, "threshold");
    edge_detection.Description(
        "Border selection. Pixels with a value higher than threshold are colored white, and the rest are colored "
        "black.");

    if (argc == 1) {
        std::cout << program.ConstructHelp();
        return 0;
    }

    try {
        program.Parse(argc, argv);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return 1;
    }

    if (!program[0].HasValue() || !program[1].HasValue()) {
        std::cerr << "Error: The input and output file are required." << std::endl;
        return 1;
    }

    BMP bmp_io;
    Image image;

    try {
        image = bmp_io.Load(program[0].Get<std::string>());
    } catch (const std::invalid_argument& e) {
        std::cerr << "Input file error. " << e.what() << std::endl;
        return 1;
    }

    for (auto it = program.OrderedSubprogsBegin(); it != program.OrderedSubprogsEnd(); ++it) {
        auto& subprog = *(*it);

        try {
            ApplySubprogram(subprog, image);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Filter error. " << e.what() << std::endl;
            return 1;
        }
    }

    bmp_io.Save(image, program[1].Get<std::string>());

    return 0;
}

void ApplySubprogram(smplcli::ProgramParameters& subprog, Image& image) {
    if (subprog.GetName() == "-crop") {
        if (!subprog[0].HasValue() || !subprog[1].HasValue()) {
            throw std::invalid_argument("crop error: width and height are required");
        }

        CropFilter crop(subprog[0].Get<int>(), subprog[1].Get<int>());
        crop.ApplyFilter(image);
    }

    else if (subprog.GetName() == "-gs") {
        GrayscaleFilter gs;
        gs.ApplyFilter(image);
    }

    else if (subprog.GetName() == "-neg") {
        NegativeFilter neg;
        neg.ApplyFilter(image);
    }

    else if (subprog.GetName() == "-sharp") {
        SharpeningFilter sharp;
        sharp.ApplyFilter(image);
    }

    else if (subprog.GetName() == "-edge") {
        if (!subprog[0].HasValue()) {
            throw std::invalid_argument("edge error: threshold is required");
        }

        EdgeDetectionFilter edge(subprog[0].Get<float>());
        edge.ApplyFilter(image);
    }
}
