////////////////////////////////////////////////////////////////////////////////
/// @brief document utilitiy functions 
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2004-2012 triagens GmbH, Cologne, Germany
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
/// @author Copyright 2012, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_ARANGOD_UTILS_DOCUMENT_HELPER_H
#define TRIAGENS_ARANGOD_UTILS_DOCUMENT_HELPER_H 1

#include "VocBase/vocbase.h"
//#include "VocBase/vocbase.h"

namespace triagens {
  namespace arango {

// -----------------------------------------------------------------------------
// --SECTION--                                              class DocumentHelper
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief scope guard for a TRI_aql_context_t*
////////////////////////////////////////////////////////////////////////////////

    class DocumentHelper {

// -----------------------------------------------------------------------------
// --SECTION--                                        constructors / destructors
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////
  
      private:

        DocumentHelper ();

        ~DocumentHelper ();

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                             public static methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////
  
      public:

////////////////////////////////////////////////////////////////////////////////
/// @brief assemble a document id from a string and a string 
////////////////////////////////////////////////////////////////////////////////

        static inline string assembleDocumentId (const string& collectionName,
                                                 const string& key) {
          return collectionName + TRI_DOCUMENT_HANDLE_SEPARATOR_STR + key;
        }

////////////////////////////////////////////////////////////////////////////////
/// @brief assemble a document id from a string and a char* key 
////////////////////////////////////////////////////////////////////////////////

        static inline string assembleDocumentId (const string& collectionName,
                                                 const TRI_voc_key_t key) {
          static const string UnknownKey = "_deleted";

          if (key == 0) {
            return assembleDocumentId(collectionName, UnknownKey);
          }

          return assembleDocumentId(collectionName, string(key));
        }

////////////////////////////////////////////////////////////////////////////////
/// @brief assemble a document id from a collection id and a string key
////////////////////////////////////////////////////////////////////////////////

        static string assembleDocumentId (TRI_vocbase_t* const vocbase,
                                          const TRI_voc_cid_t cid,  
                                          const string& key) {
          static const string UnknownCollection = "_unknown";

          TRI_vocbase_col_t const* collection = TRI_LookupCollectionByIdVocBase(vocbase, cid);
          if (collection == 0) {
            // TODO: use a better name
            return assembleDocumentId(UnknownCollection, key);
          }

          // TODO: can the name be deleted while we're using it?
          return assembleDocumentId(collection->_name, key);
        }

////////////////////////////////////////////////////////////////////////////////
/// @brief assemble a document id from a collection id and a char* key
////////////////////////////////////////////////////////////////////////////////

        static string assembleDocumentId (TRI_vocbase_t* const vocbase,
                                          const TRI_voc_cid_t cid,  
                                          const TRI_voc_key_t key) {
          static const string UnknownKey = "_deleted";

          if (key == 0) {
            return assembleDocumentId(vocbase, cid, UnknownKey); 
          }

          return assembleDocumentId(vocbase, cid, string(key));
        }

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

    };
  }
}

#endif

// Local Variables:
// mode: outline-minor
// outline-regexp: "^\\(/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|// --SECTION--\\|/// @\\}\\)"
// End: