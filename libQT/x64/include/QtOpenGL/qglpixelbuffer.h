/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtOpenGL module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QGLPIXELBUFFER_H
#define QGLPIXELBUFFER_H

#include <QtOpenGL/qgl.h>
#include <QtGui/qpaintdevice.h>

QT_BEGIN_NAMESPACE


class QGLPixelBufferPrivate;

class Q_OPENGL_EXPORT QGLPixelBuffer : public QPaintDevice
{
    Q_DECLARE_PRIVATE(QGLPixelBuffer)
public:
    QGLPixelBuffer(const QSize &size, const QGLFormat &format = QGLFormat::defaultFormat(),
                   QGLWidget *shareWidget = Q_NULLPTR);
    QGLPixelBuffer(int width, int height, const QGLFormat &format = QGLFormat::defaultFormat(),
                   QGLWidget *shareWidget = Q_NULLPTR);
    virtual ~QGLPixelBuffer();

    bool isValid() const;
    bool makeCurrent();
    bool doneCurrent();

    QGLContext *context() const;

    GLuint generateDynamicTexture() const;
    bool bindToDynamicTexture(GLuint texture);
    void releaseFromDynamicTexture();
    void updateDynamicTexture(GLuint texture_id) const;

    GLuint bindTexture(const QImage &image, GLenum target = GL_TEXTURE_2D);
    GLuint bindTexture(const QPixmap &pixmap, GLenum target = GL_TEXTURE_2D);
    GLuint bindTexture(const QString &fileName);
    void deleteTexture(GLuint texture_id);

    void drawTexture(const QRectF &target, GLuint textureId, GLenum textureTarget = GL_TEXTURE_2D);
    void drawTexture(const QPointF &point, GLuint textureId, GLenum textureTarget = GL_TEXTURE_2D);

    QSize size() const;
    Qt::HANDLE handle() const;
    QImage toImage() const;

    QPaintEngine *paintEngine() const Q_DECL_OVERRIDE;
    QGLFormat format() const;

    static bool hasOpenGLPbuffers();

protected:
    int metric(PaintDeviceMetric metric) const Q_DECL_OVERRIDE;
    int devType() const Q_DECL_OVERRIDE { return QInternal::Pbuffer; }

private:
    Q_DISABLE_COPY(QGLPixelBuffer)
    QScopedPointer<QGLPixelBufferPrivate> d_ptr;
    friend class QGLDrawable;
    friend class QGLPaintDevice;
    friend class QGLPBufferGLPaintDevice;
    friend class QGLContextPrivate;
};

QT_END_NAMESPACE

#endif // QGLPIXELBUFFER_H
