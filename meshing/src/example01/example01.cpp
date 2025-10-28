#include "mesh/io/OBJReader.hpp"
#include "mesh/io/OBJWriter.hpp"
#include "meshModeling/TriSoup_FastQEM.hpp"
#include <cfloat>
#include <thread>

using namespace AMCAX::Meshing;
using namespace AMCAX::Meshing::Mesh;
using namespace AMCAX::Meshing::Remeshing;

void Remeshing_FastQEM()
{
    // Define progress callback function
    int overall_percent{};  // Overall progress percentage
    AMCAX::Meshing::Mesh::CbFunc pro_fn =
        [&overall_percent](int _overall_percent,
            AMCAXMeshing_UNUSED bool& cancel) -> void
        {
            overall_percent = _overall_percent;
            std::cout << "[Progress] Overall progress: " << overall_percent << "%"
                << std::endl;

            // If algorithm termination is needed, set cancel to true
            if (overall_percent == 100)
                std::cout << std::endl;
        };

    IOOptions io_options;
    io_options.vertex_has_point = true;
    OBJReader<TriSoupTraits_Coord> obj_reader;
    OBJWriter<TriSoupTraits_Coord> obj_writer;

    obj_reader.read("./data/32770_sf.obj", io_options);
    for (double ratio : {0.01, 0.1, 0.3, 0.6})
    {
        FastQEM<TriSoupTraits_Coord> fast_qem(obj_reader.m_points, obj_reader.m_triangles);
        Logger::elapse_reset();
        std::thread simplify_thread(
            [&]()
            {
                fast_qem.simplify(size_t(obj_reader.m_triangles.size() * ratio), 0.1f, 20, pro_fn);
            });
        simplify_thread.join();

        auto elapsed = Logger::elapsed();
        Logger::info("FastQEM: ratio " + std::to_string(ratio) + ";  time " + std::to_string(elapsed.count()) + " s");
        obj_writer.clear();
        obj_writer.m_points = std::move(fast_qem.m_points);
        obj_writer.m_triangles = std::move(fast_qem.m_triangles);
        std::string out_filename = "FastQEM_" + std::to_string(ratio) + ".obj";
        obj_writer.write(out_filename, io_options, 10);
    }
}

int main()
{
    Remeshing_FastQEM();
}