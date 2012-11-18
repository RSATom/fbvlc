#include "FBVLC_Mac.h"

////////////////////////////////////////////////////////////////////////////////
//FBVLC_Mac class
////////////////////////////////////////////////////////////////////////////////
FBVLC_Mac::FBVLC_Mac()
{
}

FBVLC_Mac::~FBVLC_Mac()
{
}

bool FBVLC_Mac::onCoreGraphicsDraw(FB::CoreGraphicsDraw *evt, FB::PluginWindowMacCG*)
{
    FB::Rect bounds(evt->bounds);
    //FB::Rect clip(evt->clip);
    short width = bounds.right - bounds.left, height = bounds.bottom - bounds.top;

    CGContextRef cgContext(evt->context);

    CGContextSaveGState(cgContext);

    CGContextTranslateCTM(cgContext, 0.0, height);
    CGContextScaleCTM(cgContext, 1.0, -1.0);

    CGColorSpaceRef cSpace = CGColorSpaceCreateDeviceRGB();
    CGContextSetFillColorSpace(cgContext, cSpace);

    // Clear the stage.
    //CGRect rect0 = { {0,0}, {width, height} };
    //CGContextClearRect(cgContext, rect0);

    if ( m_frame_buf.size() &&
         m_frame_buf.size() >= m_media_width * m_media_height * DEF_PIXEL_BYTES )
    {
        CGContextRef bmpCtx =
            CGBitmapContextCreate(&m_frame_buf[0], m_media_width, m_media_height, 8,
                                  m_media_width * DEF_PIXEL_BYTES, cSpace, kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Little);
        CGImageRef img = CGBitmapContextCreateImage(bmpCtx);

        CGRect imgRect = {
            { (width - m_media_width) / 2, (height - m_media_height) / 2 },
            { m_media_width, m_media_height }
        };
        CGContextDrawImage(cgContext, imgRect, img);

        CGImageRelease(img);
        CGContextRelease(bmpCtx);
    }

    CGColorSpaceRelease(cSpace);
    CGContextRestoreGState(cgContext);

    return true; // This is handled
}
