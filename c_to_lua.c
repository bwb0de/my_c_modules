#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // Passa um número inteiro (por exemplo, nível do jogador)
    lua_pushinteger(L, 42);             // valor
    lua_setglobal(L, "nivel_do_jogador"); // nome da variável no Lua

    // Passa uma string
    lua_pushstring(L, "Daniel");
    lua_setglobal(L, "nome_do_jogador");

    // Agora roda um script que usará essas variáveis
    if (luaL_dofile(L, "lua_recive_C.lua") != LUA_OK) {
        printf("Erro: %s\n", lua_tostring(L, -1));
    }

    lua_close(L);
    return 0;
}
