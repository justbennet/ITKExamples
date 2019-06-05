/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageRandomNonRepeatingIteratorWithIndex.h"
#include "itkImageFileWriter.h"
#include "itkMersenneTwisterRandomVariateGenerator.h"

int main (int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0]
                  << " inputFile outputFile [percent]" << std::endl;
        return EXIT_FAILURE;
    }
    double percent = .1;
    if (argc > 3)
    {
        percent = std::stod(argv[3]);
        if (percent >= 1.0)
        {
            percent /= 100.0;
        }
    }
    using ImageType = itk::Image<unsigned char, 2>;
    using ReaderType = itk::ImageFileReader<ImageType>;
    using IteratorType = itk::ImageRandomNonRepeatingIteratorWithIndex<ImageType>;
    using WriterType = itk::ImageFileWriter<ImageType>;

    // Read the binary file
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName( argv[1] );
    reader->Update();

    // At x% of the pixels, add a uniform random value between 0 and 255
    IteratorType it(reader->GetOutput(),
                    reader->GetOutput()->GetLargestPossibleRegion());
    it.SetNumberOfSamples(reader->GetOutput()->GetLargestPossibleRegion().GetNumberOfPixels() * percent);
    std::cout << "Number of random samples: "
              << it.GetNumberOfSamples() << std::endl;
    using GeneratorType = itk::Statistics::MersenneTwisterRandomVariateGenerator;
    GeneratorType::Pointer random = GeneratorType::New();

    it.GoToBegin();
    while(!it.IsAtEnd())
    {
        it.Set(random->GetUniformVariate(0, 255));
        ++it;
    }

    // Write the file
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName( argv[2] );
    writer->SetInput(reader->GetOutput());
    writer->Update();

    return EXIT_SUCCESS;
}
