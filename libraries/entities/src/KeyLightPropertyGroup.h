//
//  KeyLightPropertyGroup.h
//  libraries/entities/src
//
//  Created by Sam Gateau on 2015/10/23.
//  Copyright 2013 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//


#ifndef hifi_KeyLightPropertyGroup_h
#define hifi_KeyLightPropertyGroup_h

#include <stdint.h>

#include <glm/glm.hpp>

#include <QtScript/QScriptEngine>
#include "EntityItemPropertiesMacros.h"
#include "PropertyGroup.h"

class EntityItemProperties;
class EncodeBitstreamParams;
class OctreePacketData;
class EntityTreeElementExtraEncodeData;
class ReadBitstreamToTreeParams;

/**jsdoc
 * A key light is defined by the following properties:
 * @typedef {object} Entities.KeyLight
 * @property {Color} color=255,255,255 - The color of the light.
 * @property {number} intensity=1 - The intensity of the light.
 * @property {Vec3} direction=0,-1,0 - The direction the light is shining.
 * @property {boolean} castShadows=false - <code>true</code> if shadows are cast, <code>false</code> if they aren't. Shadows 
 *     are cast by avatars, plus {@link Entities.EntityProperties-Model|Model} and 
 *     {@link Entities.EntityProperties-Shape|Shape} entities that have their 
 *     <code>{@link Entities.EntityProperties|canCastShadow}</code> property set to <code>true</code>.
 */
class KeyLightPropertyGroup : public PropertyGroup {
public:
    // EntityItemProperty related helpers
    virtual void copyToScriptValue(const EntityPropertyFlags& desiredProperties, QScriptValue& properties,
                                   QScriptEngine* engine, bool skipDefaults,
                                   EntityItemProperties& defaultEntityProperties) const override;
    virtual void copyFromScriptValue(const QScriptValue& object, bool& _defaultSettings) override;

    void merge(const KeyLightPropertyGroup& other);

    virtual void debugDump() const override;
    virtual void listChangedProperties(QList<QString>& out) override;

    virtual bool appendToEditPacket(OctreePacketData* packetData,
                                    EntityPropertyFlags& requestedProperties,
                                    EntityPropertyFlags& propertyFlags,
                                    EntityPropertyFlags& propertiesDidntFit,
                                    int& propertyCount,
                                    OctreeElement::AppendState& appendState) const override;

    virtual bool decodeFromEditPacket(EntityPropertyFlags& propertyFlags,
                                      const unsigned char*& dataAt, int& processedBytes) override;
    virtual void markAllChanged() override;
    virtual EntityPropertyFlags getChangedProperties() const override;

    // EntityItem related helpers
    // methods for getting/setting all properties of an entity
    virtual void getProperties(EntityItemProperties& propertiesOut) const override;

    /// returns true if something changed
    virtual bool setProperties(const EntityItemProperties& properties) override;

    virtual EntityPropertyFlags getEntityProperties(EncodeBitstreamParams& params) const override;

    virtual void appendSubclassData(OctreePacketData* packetData, EncodeBitstreamParams& params,
                                    EntityTreeElementExtraEncodeDataPointer entityTreeElementExtraEncodeData,
                                    EntityPropertyFlags& requestedProperties,
                                    EntityPropertyFlags& propertyFlags,
                                    EntityPropertyFlags& propertiesDidntFit,
                                    int& propertyCount,
                                    OctreeElement::AppendState& appendState) const override;

    virtual int readEntitySubclassDataFromBuffer(const unsigned char* data, int bytesLeftToRead,
                                                ReadBitstreamToTreeParams& args,
                                                EntityPropertyFlags& propertyFlags, bool overwriteLocalData,
                                                bool& somethingChanged) override;

    static const glm::u8vec3 DEFAULT_KEYLIGHT_COLOR;
    static const float DEFAULT_KEYLIGHT_INTENSITY;
    static const float DEFAULT_KEYLIGHT_AMBIENT_INTENSITY;
    static const glm::vec3 DEFAULT_KEYLIGHT_DIRECTION;
    static const bool DEFAULT_KEYLIGHT_CAST_SHADOWS;

    DEFINE_PROPERTY_REF(PROP_KEYLIGHT_COLOR, Color, color, glm::u8vec3, DEFAULT_KEYLIGHT_COLOR);
    DEFINE_PROPERTY(PROP_KEYLIGHT_INTENSITY, Intensity, intensity, float, DEFAULT_KEYLIGHT_INTENSITY);
    DEFINE_PROPERTY_REF(PROP_KEYLIGHT_DIRECTION, Direction, direction, glm::vec3, DEFAULT_KEYLIGHT_DIRECTION);
    DEFINE_PROPERTY(PROP_KEYLIGHT_CAST_SHADOW, CastShadows, castShadows, bool, DEFAULT_KEYLIGHT_CAST_SHADOWS);
};

#endif // hifi_KeyLightPropertyGroup_h
