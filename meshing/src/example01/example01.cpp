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
    bool first = true;
    int  stage, current, total;

    FastQEM<TriSoupTraits_Coord>::ProFn pro_fn =
        [&first, &stage, &current, &total](int _stage, int _current, int _total,
            AMCAXMeshing_UNUSED bool& cancel) -> void
        {
            stage = _stage;
            current = _current;
            total = _total;

            if (!first)
                std::cout << "\r\033[K"; std::cout << "stage: " << _stage << "/"
                << FastQEM<TriSoupTraits_Coord>::Total << ", process: " << current
                << "/" << total;
            first = false;
            // set cancel to true if you want to terminate the algorithm
            if (stage == FastQEM<TriSoupTraits_Coord>::Stage::Total)
                std::cout << std::endl;
        };

    IOOptions io_options;
    io_options.vertex_has_point = true;
    OBJReader<TriSoupTraits_Coord> obj_reader;
    OBJWriter<TriSoupTraits_Coord> obj_writer;

    obj_reader.read("./data/32770_sf.obj", io_options);
    for (double ratio : {0.01, 0.1, 0.3, 0.6})
    {
        first = true;
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