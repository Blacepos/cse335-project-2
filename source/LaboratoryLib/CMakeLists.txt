project(LaboratoryLib)

set(SOURCE_FILES
        pch.h
        Laboratory.h Laboratory.cpp LaboratoryFactory.cpp LaboratoryFactory.h LaboratoryStandin.cpp LaboratoryStandin.h
        Polygon.cpp Polygon.h
        LaboratoryDialog.cpp LaboratoryDialog.h include/laboratory-api.h GraphicsHelper.cpp GraphicsHelper.h Sparky.cpp Sparky.h LabSwitch.cpp LabSwitch.h LaboratoryActual.cpp LaboratoryActual.h ActualLabFactory1.cpp ActualLabFactory1.h ActualLabFactory2.cpp ActualLabFactory2.h Component.cpp Component.h Shape.cpp Shape.h ZPM.cpp ZPM.h EquipmentRack.cpp EquipmentRack.h PolyComponent.cpp PolyComponent.h PowerSource.cpp PowerSource.h PowerSink.cpp PowerSink.h PowerSinkUser.cpp PowerSinkUser.h Light.cpp Light.h Distribution.cpp Distribution.h Switch.cpp Switch.h Winch.cpp Winch.h Orbs.cpp Orbs.h MotionSource.cpp MotionSource.h MotionSinkUser.cpp MotionSinkUser.h Cable.cpp Cable.h CableFactory.cpp CableFactory.h BezierEnd.cpp BezierEnd.h Rheostat.cpp Rheostat.h VoltageMeter.cpp VoltageMeter.h Relay.cpp Relay.h)

find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)