include_guard()
message("middleware_lwip_apps_httpd component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/apps/http/httpd.c
)


include(middleware_lwip_MIMX9352)

include(middleware_lwip_apps_httpd_support_MIMX9352)
