
#GSL from Microsoft project wide integrtation
hunter_add_package(Microsoft.GSL)
hunter_add_package(nlohmann_json)
#Find librairies loaded by hunter
find_package(Microsoft.GSL CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
#Link the library for all the projects
link_libraries(Microsoft.GSL::GSL)
link_libraries(nlohmann_json::nlohmann_json)



#GSL from Microsoft project wide integrtation
hunter_add_package(GTest)
hunter_add_package(nlohmann_json)
