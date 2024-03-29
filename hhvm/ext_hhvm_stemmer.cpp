/*
   +----------------------------------------------------------------------+
   | Stemmer for HHVM                                                     |
   +----------------------------------------------------------------------+
   | 									 								  |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#define FFI_LIB "libstemmer.so"

#include "./libstemmer_c/include/libstemmer.h"

#include "hphp/runtime/ext/extension.h"

#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <vector>

#include <folly/Conv.h>
#include <folly/ScopeGuard.h>
#include <folly/String.h>

#include "hphp/util/network.h"
#include "hphp/util/text-util.h"
#include "hphp/util/timer.h"

#include "hphp/system/systemlib.h"

#include "hphp/runtime/base/builtin-functions.h"
#include "hphp/runtime/base/comparisons.h"
#include "hphp/runtime/base/extended-logger.h"
#include "hphp/runtime/base/runtime-option.h"
#include "hphp/runtime/vm/jit/translator-inline.h"

#include "hphp/runtime/vm/native-data.h"

namespace HPHP {
	
	Variant HHVM_FUNCTION(hh_stem,  const String& language, const String& word, const String& enc) {
		if (language.empty()) {
			raise_warning("Language cannot be empty");
			return false;
		}
		
		sb_stemmer * sb;
		
		sb = sb_stemmer_new(language.data(), enc.data());

		if (sb == NULL) {
			return false;
		}
		
		const char* result = (const char*)sb_stemmer_stem(sb, (unsigned char *)word.data(), word.size());
		
		sb_stemmer_delete(sb);
		
		if (result == NULL) {
			raise_warning("Stemmer_apply failed");
			return false;
		}
		
		return String(result);
		
	}
	
	Array HHVM_FUNCTION(stemmer_list) {
		Array ret;

		int i = 0;
		const char **list = sb_stemmer_list();
		for (const char **cur = list; *cur != NULL; cur++) {
			ret.set(i++, *cur);
		}
		return ret;
	}
	
	
	class hhvm_stemmerExtension : public Extension {
		public:
			hhvm_stemmerExtension(): Extension("hhvm_stemmer", "0.1.0") {}

		void moduleInit() override {
			HHVM_FE(hh_stem);
			HHVM_FE(stemmer_list);

			loadSystemlib();
		}
	} s_hhvm_stemmer_extension;

	HHVM_GET_MODULE(hhvm_stemmer);
}