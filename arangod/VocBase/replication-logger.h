////////////////////////////////////////////////////////////////////////////////
/// @brief replication logger
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2004-2013 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Jan Steemann
/// @author Copyright 2011-2013, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_VOC_BASE_REPLICATION_LOGGER_H
#define TRIAGENS_VOC_BASE_REPLICATION_LOGGER_H 1

#include "BasicsC/common.h"

#include "BasicsC/locks.h"

#include "VocBase/document-collection.h"
#include "VocBase/vocbase.h"
#include "VocBase/voc-types.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// --SECTION--                                              forward declarations
// -----------------------------------------------------------------------------

struct TRI_col_info_s;
struct TRI_df_marker_s;
struct TRI_document_collection_s;
struct TRI_doc_mptr_s;
struct TRI_json_s;
struct TRI_transaction_s;
struct TRI_vocbase_col_s;
struct TRI_vocbase_s;

// -----------------------------------------------------------------------------
// --SECTION--                                                REPLICATION LOGGER
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// --SECTION--                                                    public defines
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup VocBase
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief default maximum number of logs to be kept 
////////////////////////////////////////////////////////////////////////////////

#define TRI_REPLICATION_DEFAULT_LOG_COUNT (16)

////////////////////////////////////////////////////////////////////////////////
/// @brief minimum number of logs to be kept 
////////////////////////////////////////////////////////////////////////////////

#define TRI_REPLICATION_MIN_LOG_COUNT (2)

////////////////////////////////////////////////////////////////////////////////
/// @brief default size for each log file
////////////////////////////////////////////////////////////////////////////////

#define TRI_REPLICATION_DEFAULT_LOG_SIZE  (64 * 1024 * 1024)

////////////////////////////////////////////////////////////////////////////////
/// @brief minimum size for each log file
////////////////////////////////////////////////////////////////////////////////

#define TRI_REPLICATION_MIN_LOG_SIZE (1 * 1024 * 1024)

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                      public types
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup VocBase
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief replication setup
////////////////////////////////////////////////////////////////////////////////

typedef struct TRI_replication_setup_s {
  char*    _path;
  size_t   _maxLogs;
  int64_t  _logSize;
  bool     _waitForSync;
  bool     _active;
}
TRI_replication_setup_t;

////////////////////////////////////////////////////////////////////////////////
/// @brief context information for replication logging
////////////////////////////////////////////////////////////////////////////////

typedef struct TRI_replication_logger_s {
  TRI_read_write_lock_t    _lock;
  TRI_vector_pointer_t     _logs;
  TRI_replication_setup_t  _setup;
  bool                     _active;
}
TRI_replication_logger_t;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                  public functions
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup VocBase
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief create a replication logger
////////////////////////////////////////////////////////////////////////////////

TRI_replication_logger_t* TRI_CreateReplicationLogger (TRI_replication_setup_t const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief destroy a replication logger
////////////////////////////////////////////////////////////////////////////////

void TRI_DestroyReplicationLogger (TRI_replication_logger_t*);

////////////////////////////////////////////////////////////////////////////////
/// @brief free a replication logger
////////////////////////////////////////////////////////////////////////////////

void TRI_FreeReplicationLogger (TRI_replication_logger_t*);

////////////////////////////////////////////////////////////////////////////////
/// @brief start the replication logger
////////////////////////////////////////////////////////////////////////////////

int TRI_StartReplicationLogger (TRI_replication_logger_t*);

////////////////////////////////////////////////////////////////////////////////
/// @brief stop the replication logger
////////////////////////////////////////////////////////////////////////////////

int TRI_StopReplicationLogger (TRI_replication_logger_t*);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                       REPLICATION
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// --SECTION--                                                  public functions
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup VocBase
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief replicate a transaction
////////////////////////////////////////////////////////////////////////////////

#ifdef TRI_ENABLE_REPLICATION

int TRI_TransactionReplication (struct TRI_vocbase_s*,
                                struct TRI_transaction_s const*);

#else

#define TRI_TransactionReplication(...)

#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief replicate a "create collection" operation
////////////////////////////////////////////////////////////////////////////////

#ifdef TRI_ENABLE_REPLICATION

int TRI_CreateCollectionReplication (struct TRI_vocbase_s*,
                                     TRI_voc_cid_t, 
                                     struct TRI_json_s const*);

#else

#define TRI_CreateCollectionReplication(...)

#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief replicate a "drop collection" operation
////////////////////////////////////////////////////////////////////////////////

#ifdef TRI_ENABLE_REPLICATION

int TRI_DropCollectionReplication (struct TRI_vocbase_s*,
                                   TRI_voc_cid_t);

#else

#define TRI_DropCollectionReplication(...)

#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief replicate a "rename collection" operation
////////////////////////////////////////////////////////////////////////////////

#ifdef TRI_ENABLE_REPLICATION

int TRI_RenameCollectionReplication (struct TRI_vocbase_s*,
                                     TRI_voc_cid_t,
                                     char const*);

#else

#define TRI_RenameCollectionReplication(...)

#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief replicate a "change collection properties" operation
////////////////////////////////////////////////////////////////////////////////

#ifdef TRI_ENABLE_REPLICATION

int TRI_ChangePropertiesCollectionReplication (struct TRI_vocbase_s*,
                                               TRI_voc_cid_t,
                                               struct TRI_json_s const*);

#else

#define TRI_ChangePropertiesCollectionReplication(...)

#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief replicate a "create index" operation
////////////////////////////////////////////////////////////////////////////////

#ifdef TRI_ENABLE_REPLICATION

int TRI_CreateIndexReplication (struct TRI_vocbase_s*,
                                TRI_voc_cid_t,
                                TRI_idx_iid_t,
                                struct TRI_json_s const*);

#else

#define TRI_CreateIndexReplication(...)

#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief replicate a "drop index" operation
////////////////////////////////////////////////////////////////////////////////

#ifdef TRI_ENABLE_REPLICATION

int TRI_DropIndexReplication (struct TRI_vocbase_s*,
                              TRI_voc_cid_t,
                              TRI_idx_iid_t iid);

#else

#define TRI_DropIndexReplication(...)

#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief replicate a document operation
////////////////////////////////////////////////////////////////////////////////

#ifdef TRI_ENABLE_REPLICATION

int TRI_DocumentReplication (struct TRI_vocbase_s*,
                             struct TRI_document_collection_s*,
                             TRI_voc_document_operation_e,
                             struct TRI_df_marker_s const*,
                             struct TRI_doc_mptr_s const*);

#else

#define TRI_DocumentReplication(...)

#endif

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif

// Local Variables:
// mode: outline-minor
// outline-regexp: "/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|/// @page\\|// --SECTION--\\|/// @\\}"
// End:
