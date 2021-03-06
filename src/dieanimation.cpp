#include "dieanimation.h"

dieAnimation::dieAnimation(QPointF p, QSGNode *node, QSGMaterial *material, QObject *parent) : QObject(parent) {
	this->node = node;
	onode = new QSGOpacityNode;
	gnode = new QSGGeometryNode;
	geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0);
	geometry->setLineWidth(PARTICLESIZE);
	geometry->setDrawingMode(GL_POINTS);
	gnode->setGeometry(geometry);
	gnode->setFlag(QSGNode::OwnsGeometry);
	gnode->setMaterial(material);
	gnode->setFlag(QSGNode::OwnsMaterial);
	geometry->allocate(PARTICLECOUNT);
	vertices = geometry->vertexDataAsPoint2D();
	for (int i = 0; i < PARTICLECOUNT; i++) {
		vertices[i].set(p.x(), p.y());
		directions[i] = QPointF(-.5+segment::randFloat(), -.5+segment::randFloat());
	}
	onode->appendChildNode(gnode);
	node->appendChildNode(onode);
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(progress()));
	initialTime = QTime::currentTime();
	lastTime = initialTime;
	timer->start(30);
}

void dieAnimation::progress() {
	float timeSinceStart = initialTime.msecsTo(QTime::currentTime());
	if (timeSinceStart >= PARTICLELIFETIME) {
		//cleanup
		timer->stop();
		node->removeChildNode(onode);
		onode->removeChildNode(gnode);
		free(geometry);
		free(gnode);
		free(onode);
	} else {
		float deltat = (float) lastTime.msecsTo(QTime::currentTime())/1000;
		lastTime = QTime::currentTime();
		progress(deltat, timeSinceStart);
	}
}

void dieAnimation::progress(float deltat, float timeSinceStart) {
	for (int i = 0; i < PARTICLECOUNT; i++) {
		vertices[i].set(vertices[i].x+deltat*PARTICLEVELOCITY*directions[i].x(), vertices[i].y+deltat*PARTICLEVELOCITY*directions[i].y());
	}
	onode->setOpacity(1 - timeSinceStart / PARTICLELIFETIME);
	gnode->markDirty(QSGNode::DirtyGeometry);
}
