//TODO:
//handle STREAM vs STATIC draw allocation for meshes
//animations
//bounding box/scale/etc?

#include "ofModel.h"

//--------------------------------------------------------------
ofModel::ofModel(){
	renderMethod = OF_MESH_USING_DEFAULT_RENDERER;
	bUsingTextures = false;
}

//--------------------------------------------------------------
ofModel::~ofModel(){

}

//--------------------------------------------------------------
void ofModel::bindTextureForMesh(int id){
	int texId = textureLinks[id];
	if(texId!=-1){
		textures.at(texId).getTextureReference().bind();	
	}
}

//--------------------------------------------------------------
void ofModel::unbindTextureForMesh(int id){
	int texId = textureLinks[id];
	if(texId!=-1){
		textures.at(texId).getTextureReference().unbind();	
	}
}

//--------------------------------------------------------------
void ofModel::drawWireframe(){
	for (int i =0; i < (int)meshes.size();i++){
		
		if(!meshes.at(i).enableIndices()){
			ofLog(OF_LOG_WARNING, "no indices in mesh " + ofToString(i));
		}

		bool goodToTexture = bUsingTextures && meshes.at(i).getTexCoordsEnabled();
		if(goodToTexture){
			bindTextureForMesh(i);
		}

		meshes.at(i).setRenderMethod(renderMethod);
		
		meshes.at(i).drawWireframe();
		
		if(goodToTexture){
			unbindTextureForMesh(i);
		}
	}
}

//--------------------------------------------------------------
void ofModel::drawFaces(){
	for (int i =0; i < (int)meshes.size();i++){
		
		if(!meshes.at(i).enableIndices()){
			ofLog(OF_LOG_WARNING, "no indices in mesh " + ofToString(i));
		}
		
		bool goodToTexture = bUsingTextures && meshes.at(i).getTexCoordsEnabled();
		if(goodToTexture){
			bindTextureForMesh(i);
		}
		meshes.at(i).setRenderMethod(renderMethod);
		
		meshes.at(i).drawFaces();
		
		if(goodToTexture){
			unbindTextureForMesh(i);
		}
	}
}

//--------------------------------------------------------------
void ofModel::drawVertices(){
	for (int i =0; i < (int)meshes.size();i++){
		
		bool goodToTexture = bUsingTextures && meshes.at(i).getTexCoordsEnabled();
		if(goodToTexture){
			bindTextureForMesh(i);
		}

		meshes.at(i).setRenderMethod(renderMethod);
		
		meshes.at(i).drawVertices();
		
		if(goodToTexture){
			unbindTextureForMesh(i);
		}
	}
}


ofMesh* ofModel::getMesh(unsigned int nIndex) {
	if(nIndex < meshes.size()) {
		return &meshes.at(nIndex);
	}
	return NULL;
}

ofMesh* ofModel::getMesh(string sName) {
	ofNamedMeshes::iterator it = named_meshes.find(sName);
	if(it != named_meshes.end()) {
		return it->second;
	}
	return NULL; 
}

void ofModel::listMeshNames() {
	ofNamedMeshes::iterator it = named_meshes.begin();
	while(it != named_meshes.end()) {
		cout << "Mesh: '" << it->first << "'" << std::endl;
		++it;
	}
}


//--------------------------------------------------------------

void ofModel::enableTextures(){
	bUsingTextures = true;
	for (int i =0; i < (int)meshes.size();i++){
		meshes.at(i).enableTexCoords();
	}
}

//--------------------------------------------------------------
void ofModel::enableNormals(){
	for (int i =0; i < (int)meshes.size();i++){
		meshes.at(i).enableNormals();
	}
}

//--------------------------------------------------------------
void ofModel::enableColors(){
	for (int i =0; i < (int)meshes.size();i++){
		meshes.at(i).enableColors();
	}
}

//--------------------------------------------------------------
void ofModel::disableTextures(){
	bUsingTextures = false;
	for (int i =0; i < (int)meshes.size();i++){
		meshes.at(i).disableTexCoords();
	}
}

//--------------------------------------------------------------
void ofModel::disableNormals(){
	for (int i =0; i < (int)meshes.size();i++){
		meshes.at(i).disableNormals();
	}
}

//--------------------------------------------------------------
void ofModel::disableColors(){
	for (int i =0; i < (int)meshes.size();i++){
		meshes.at(i).disableColors();
	}
}

//--------------------------------------------------------------
void ofModel::setRenderMethod(meshRenderMethod m){
	renderMethod = m;
}
