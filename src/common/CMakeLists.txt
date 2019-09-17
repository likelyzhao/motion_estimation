file(GLOB tmp *.cpp *.hpp *.h)
set(${PROJECT_NAME}_src ${${PROJECT_NAME}_src} ${tmp})

set(${PROJECT_NAME}_src ${${PROJECT_NAME}_src} PARENT_SCOPE)
