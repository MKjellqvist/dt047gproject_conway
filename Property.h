//
// Created by martin on 2023-10-03.
//

#ifndef DT047GPROJECT_CONWAY_PROPERTY_H
#define DT047GPROJECT_CONWAY_PROPERTY_H
namespace conway{

template<typename ConnectedTo, typename ValueType>
class Property {
    using value_listener = void(ValueType&, Property* );
    ValueType& value(){

    }
};

}

#endif //DT047GPROJECT_CONWAY_PROPERTY_H
