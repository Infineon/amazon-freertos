# AFR HTTPS demo
afr_demo_module(https)

afr_write_demo_metadata("
https:
  id: HTTPS_SYNC_DOWNLOAD_DEMO
  description: Examples that demonstrate the HTTPS Client
  display_name: HTTPS Client Demos
  configuredDemos:
    - exampleName: HTTPS_SYNC_DOWNLOAD_DEMO
      description: HTTPS client demo will perform download task using synchronous method
      defaultChoice: true
    - exampleName: HTTPS_ASYNC_DOWNLOAD_DEMO
      description: HTTPS client demo will perform download task using asynchronous method
      defaultChoice: false
    - exampleName: HTTPS_SYNC_UPLOAD_DEMO
      description: HTTPS client demo will perform upload task using synchronous method
      defaultChoice: false
    - exampleName: HTTPS_ASYNC_UPLOAD_DEMO
      description: HTTPS client demo will perform upload task using asynchronous method
      defaultChoice: false
")

afr_module_sources(
    ${AFR_CURRENT_MODULE}
    INTERFACE
        "${CMAKE_CURRENT_LIST_DIR}/iot_demo_https_s3_download_sync.c"
        "${CMAKE_CURRENT_LIST_DIR}/iot_demo_https_s3_download_async.c"
        "${CMAKE_CURRENT_LIST_DIR}/iot_demo_https_s3_upload_sync.c"
        "${CMAKE_CURRENT_LIST_DIR}/iot_demo_https_s3_upload_async.c"
        "${CMAKE_CURRENT_LIST_DIR}/iot_demo_https_common.c"
)
afr_module_dependencies(
    ${AFR_CURRENT_MODULE}
    INTERFACE
        AFR::https
)
