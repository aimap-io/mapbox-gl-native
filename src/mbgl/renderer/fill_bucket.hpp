#pragma once

#include <mbgl/renderer/bucket.hpp>
#include <mbgl/tile/geometry_tile.hpp>
#include <mbgl/geometry/elements_buffer.hpp>
#include <mbgl/geometry/fill_buffer.hpp>

#include <clipper/clipper.hpp>
#include <libtess2/tesselator.h>

#include <vector>
#include <memory>

namespace mbgl {

class FillVertexBuffer;
class OutlineShader;
class OutlinePatternShader;
class PlainShader;
class PatternShader;

class FillBucket : public Bucket {

    static void *alloc(void *data, unsigned int size);
    static void *realloc(void *data, void *ptr, unsigned int size);
    static void free(void *userData, void *ptr);

    typedef ElementGroup<2> TriangleGroup;
    typedef ElementGroup<2> LineGroup;

public:
    FillBucket();
    ~FillBucket() override;

    void upload(gl::ObjectStore&) override;
    void render(Painter&, const StyleLayer&, const UnwrappedTileID&, const mat4&) override;
    bool hasData() const override;
    bool needsClipping() const override;

    void addGeometry(const GeometryCollection&);
    void tessellate();

    void drawElements(PlainShader&, gl::ObjectStore&);
    void drawElements(PatternShader&, gl::ObjectStore&);
    void drawVertices(OutlineShader&, gl::ObjectStore&);
    void drawVertices(OutlinePatternShader&, gl::ObjectStore&);

private:
    TESSalloc *allocator;
    TESStesselator *tesselator;
    ClipperLib::Clipper clipper;

    FillVertexBuffer vertexBuffer;
    TriangleElementsBuffer triangleElementsBuffer;
    LineElementsBuffer lineElementsBuffer;

    std::vector<std::unique_ptr<TriangleGroup>> triangleGroups;
    std::vector<std::unique_ptr<LineGroup>> lineGroups;

    std::vector<ClipperLib::IntPoint> line;
    bool hasVertices = false;

    static const int vertexSize = 2;
    static const int stride = sizeof(TESSreal) * vertexSize;
    static const int vertices_per_group = 3;
};

} // namespace mbgl
