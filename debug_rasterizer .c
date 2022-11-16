#include "header_files/debug_rasterizer.h"

/* Rasterize given Mesh by sorting the triangles by Y, then by X and finally, passing them to the appropriate functions according to their charakteristics. */
/* Translates the Mesh's Triangles from world to Screen Coordinates. */
const static void rasterize(const Mesh c) {

    SCMesh scmesh;
    scmesh.sct = calloc(c.indexes, sizeof(SCTriangle));

    if (!scmesh.sct)
        fprintf(stderr, "Could not allocate memory - rasterize() - calloc\n");

    scmesh.indexes = c.indexes;

    for (int i = 0; i < c.indexes; i++) {
        for (int j = 0; j < 3; j++) {

            scmesh.sct[i].scv[j].x = XWorldToScreen;
            scmesh.sct[i].scv[j].y = YWorldToScreen;
            scmesh.sct[i].z[j] = c.t[i].v[j].z;
            scmesh.sct[i].color = c.t[i].color;
        }
    }
    draw(scmesh);
    free(scmesh.sct);
}
/* Draws the Mesh's Triangles on screen in 2D coordinates. */
const static void draw(const SCMesh sc) {

    XGCValues gclines, gcfill;
    /* Lines drawing GC */
    gclines.graphics_exposures = False;
    gclines.line_width = 3;
    gclines.foreground = 0xffffff;
    GC gcl = XCreateGC(displ, win, GCGraphicsExposures | GCForeground | GCLineWidth, &gclines);
    /* Fill rectangle GC */
    gcfill.graphics_exposures = False;
    GC gcf = XCreateGC(displ, win, GCGraphicsExposures, &gcfill);

    int vindex = 1;
    for (int i = 0; i < sc.indexes; i++) {
        gcfill.foreground = sc.sct[i].color;
        XChangeGC(displ, gcf, GCForeground, &gcfill);

        for (int j = 0; j < 3; j++) {

            if (j == 2)
                vindex = 0;
            XDrawLine(displ, win, gcl, sc.sct[i].scv[j].x, sc.sct[i].scv[j].y, sc.sct[i].scv[vindex].x, sc.sct[i].scv[vindex].y);
            vindex++;
        }
        XFillPolygon(displ, win, gcf, sc.sct[i].scv, 3, Convex, CoordModeOrigin);
    }
    XFreeGC(displ, gcf);
    XFreeGC(displ, gcl);
}

