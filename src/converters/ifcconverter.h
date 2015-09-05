/*
 * Plant Mock-Up Converter
 *
 * Copyright (c) 2013, EDF. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 */

#ifndef IFCCONVERTER_H
#define IFCCONVERTER_H

#include "../api/rvmreader.h"
#include "../api/rvmmeshhelper.h"

#include <ifcpp/model/IfcPPModel.h>

#include <stack>

class IfcOwnerHistory;
class IfcRelAggregates;
class IfcLocalPlacement;
class IfcObjectDefinition;
class IfcGeometricRepresentationContext;
class IfcRepresentationItem;
class IfcMaterial;
class IfcPropertySet;
class IfcPPEntity;

class IFCConverter : public RVMReader
{
    public:
        IFCConverter(const std::string& filename);
        virtual ~IFCConverter();

        virtual void startDocument();
        virtual void endDocument();

        virtual void startHeader(const std::string& banner, const std::string& fileNote, const std::string& date, const std::string& user, const std::string& encoding);
        virtual void endHeader();

        virtual void startModel(const std::string& projectName, const std::string& name);
        virtual void endModel();

        virtual void startGroup(const std::string& name, const Vector3F& translation, const int& materialId);
        virtual void endGroup();

        virtual void startMetaData();
        virtual void endMetaData();

        virtual void startMetaDataPair(const std::string& name, const std::string& value);
        virtual void endMetaDataPair();

        virtual void startPyramid(const std::vector<float>& matrix,
                                  const float& xbottom,
                                  const float& ybottom,
                                  const float& xtop,
                                  const float& ytop,
                                  const float& height,
                                  const float& xoffset,
                                  const float& yoffset);
        virtual void endPyramid();

        virtual void startBox(const std::vector<float>& matrix,
                              const float& xlength,
                              const float& ylength,
                              const float& zlength);
        virtual void endBox();

        virtual void startRectangularTorus(const std::vector<float>& matrix,
                                           const float& rinside,
                                           const float& routside,
                                           const float& height,
                                           const float& angle);
        virtual void endRectangularTorus();

        virtual void startCircularTorus(const std::vector<float>& matrix,
                                        const float& rinside,
                                        const float& routside,
                                        const float& angle);
        virtual void endCircularTorus();

        virtual void startEllipticalDish(const std::vector<float>& matrix,
                                         const float& diameter,
                                         const float& radius);
        virtual void endEllipticalDish();

        virtual void startSphericalDish(const std::vector<float>& matrix,
                                        const float& diameter,
                                        const float& height);
        virtual void endSphericalDish();

        virtual void startSnout(const std::vector<float>& matrix,
                                const float& dtop,
                                const float& dbottom,
                                const float& height,
                                const float& xoffset,
                                const float& yoffset,
                                const float& unknown1,
                                const float& unknown2,
                                const float& unknown3,
                                const float& unknown4);
        virtual void endSnout();

        virtual void startCylinder(const std::vector<float>& matrix,
                                   const float& radius,
                                   const float& height);
        virtual void endCylinder();

        virtual void startSphere(const std::vector<float>& matrix,
                                 const float& diameter);
        virtual void endSphere();

        virtual void startLine(const std::vector<float>& matrix,
                               const float& startx,
                               const float& endx);
        virtual void endLine();

        virtual void startFacetGroup(const std::vector<float>& matrix,
                                     const FGroup& vertexes);
        virtual void endFacetGroup();

    private:
        shared_ptr<IfcPPModel>                          m_model;
        shared_ptr<IfcOwnerHistory>                     m_owner_history;
        shared_ptr<IfcGeometricRepresentationContext>   m_context;
        std::string                                     m_filename;
        std::stack<shared_ptr<IfcRelAggregates> >       m_relationStack;
        std::map<int, shared_ptr<IfcMaterial> >         m_materials;
        shared_ptr<IfcPropertySet>                      m_propertySet;
        int                                             m_currentEntityId;

        shared_ptr<IfcOwnerHistory> createOwnerHistory(const std::string &name);
        shared_ptr<IfcMaterial> createMaterial(int id);
        void insertEntity(shared_ptr<IfcPPEntity> e);
        void initModel();
        void pushParentRelation(shared_ptr<IfcObjectDefinition> parent);
        void addSurfaceModelToShape(shared_ptr<IfcRepresentationItem> item);
        void writeMesh(const Mesh &mesh, const Eigen::Matrix4f& matrix);
};

#endif // IFCCONVERTER_H
