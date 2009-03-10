/*
   SSSD

   System Database Header

   Copyright (C) Simo Sorce <ssorce@redhat.com>	2008

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __SYS_DB_H__
#define __SYS_DB_H__

#include "ldb.h"
#include "confdb/confdb.h"

#define SYSDB_CONF_SECTION "config/sysdb"
#define SYSDB_FILE "sssd.ldb"

#define SYSDB_BASE "cn=sysdb"
#define SYSDB_DOM_BASE "cn=%s,cn=sysdb"
#define SYSDB_TMPL_USER_BASE "cn=users,cn=%s,"SYSDB_BASE
#define SYSDB_TMPL_GROUP_BASE "cn=groups,cn=%s,"SYSDB_BASE

#define SYSDB_USER_CLASS "user"
#define SYSDB_GROUP_CLASS "group"

#define SYSDB_NAME "name"

#define SYSDB_NEXTID "nextID"
#define SYSDB_UIDNUM "uidNumber"
#define SYSDB_GIDNUM "gidNumber"
#define SYSDB_CREATE_TIME "createTimestamp"

#define SYSDB_PWD "userPassword"
#define SYSDB_FULLNAME "fullName"
#define SYSDB_HOMEDIR "homeDirectory"
#define SYSDB_SHELL "loginShell"
#define SYSDB_MEMBEROF "memberOf"
#define SYSDB_DISABLED "disabled"

#define SYSDB_MEMBER "member"
#define SYSDB_LEGACY_MEMBER "memberUid"

#define SYSDB_DEFAULTGROUP "defaultGroup"
#define SYSDB_GECOS "gecos"
#define SYSDB_LOCALE "locale"
#define SYSDB_KEYBOARD "keyboard"
#define SYSDB_SESSION "session"
#define SYSDB_LAST_LOGIN "lastLogin"
#define SYSDB_USERPIC "userPicture"

#define SYSDB_LAST_UPDATE "lastUpdate"

#define SYSDB_NEXTID_FILTER "("SYSDB_NEXTID"=*)"

#define SYSDB_UC "objectclass="SYSDB_USER_CLASS
#define SYSDB_GC "objectclass="SYSDB_GROUP_CLASS
#define SYSDB_MPGC "|("SYSDB_UC")("SYSDB_GC")"

#define SYSDB_PWNAM_FILTER "(&("SYSDB_UC")("SYSDB_NAME"=%s))"
#define SYSDB_PWUID_FILTER "(&("SYSDB_UC")("SYSDB_UIDNUM"=%lu))"
#define SYSDB_PWENT_FILTER "("SYSDB_UC")"

#define SYSDB_GRNAM_FILTER "(&("SYSDB_GC")("SYSDB_NAME"=%s))"
#define SYSDB_GRNA2_FILTER "(&("SYSDB_UC")("SYSDB_MEMBEROF"=%s))"
#define SYSDB_GRGID_FILTER "(&("SYSDB_GC")("SYSDB_GIDNUM"=%lu))"
#define SYSDB_GRENT_FILTER "("SYSDB_GC")"
#define SYSDB_GRNAM_MPG_FILTER "(&("SYSDB_MPGC")("SYSDB_NAME"=%s))"
#define SYSDB_GRGID_MPG_FILTER "(&("SYSDB_MPGC")("SYSDB_GIDNUM"=%lu))"
#define SYSDB_GRENT_MPG_FILTER "("SYSDB_MPGC")"

#define SYSDB_INITGR_FILTER "(&("SYSDB_GC")("SYSDB_GIDNUM"=*))"

#define SYSDB_INITGR_LEGACY_FILTER "(&("SYSDB_GC")("SYSDB_LEGACY_MEMBER"=%s))"

#define SYSDB_GETCACHED_FILTER "(&"SYSDB_UC")("SYSDB_LAST_LOGIN">=%lu))"

#define SYSDB_CHECK_FILTER "(&(|("SYSDB_UC")("SYSDB_GC"))("SYSDB_NAME"=%s))"

#define SYSDB_PW_ATTRS {SYSDB_NAME, SYSDB_UIDNUM, \
                        SYSDB_GIDNUM, SYSDB_FULLNAME, \
                        SYSDB_HOMEDIR, SYSDB_SHELL, \
                        SYSDB_LAST_UPDATE, \
                        "objectClass", \
                        NULL}
#define SYSDB_USER_ATTRS {SYSDB_DEFAULTGROUP, \
                          SYSDB_GECOS, \
                          SYSDB_HOMEDIR, \
                          SYSDB_SHELL, \
                          SYSDB_FULLNAME, \
                          SYSDB_LOCALE, \
                          SYSDB_KEYBOARD, \
                          SYSDB_SESSION, \
                          SYSDB_LAST_LOGIN, \
                          SYSDB_USERPIC, \
                          SYSDB_LAST_UPDATE, \
                          NULL}
#define SYSDB_GRNAM_ATTRS {SYSDB_NAME, SYSDB_GIDNUM, \
                           SYSDB_LAST_UPDATE, SYSDB_LEGACY_MEMBER, \
                           "objectClass", \
                           NULL}
#define SYSDB_GRPW_ATTRS {SYSDB_NAME, SYSDB_LAST_UPDATE, \
                          "objectClass", \
                          NULL}

#define SYSDB_INITGR_ATTR "memberof"
#define SYSDB_INITGR_ATTRS {SYSDB_GIDNUM, SYSDB_LAST_UPDATE, \
                            "objectClass", \
                            NULL}

#define SYSDB_TMPL_USER SYSDB_NAME"=%s,"SYSDB_TMPL_USER_BASE
#define SYSDB_TMPL_GROUP SYSDB_NAME"=%s,"SYSDB_TMPL_GROUP_BASE

struct confdb_ctx;
struct sysdb_ctx;
struct sysdb_req;

struct sysdb_attrs {
    int num;
    struct ldb_message_element *a;
};

/* sysdb_attrs helper functions */
struct sysdb_attrs *sysdb_new_attrs(TALLOC_CTX *memctx);
int sysdb_attrs_add_val(struct sysdb_attrs *attrs,
                        const char *name, const struct ldb_val *val);
int sysdb_attrs_add_string(struct sysdb_attrs *attrs,
                           const char *name, const char *str);
int sysdb_attrs_add_long(struct sysdb_attrs *attrs,
                         const char *name, long value);

/* convert an ldb error into an errno error */
int sysdb_error_to_errno(int ldberr);

/* callbacks */
typedef void (*sysdb_callback_t)(void *, int, struct ldb_result *);
typedef void (*sysdb_req_fn_t)(struct sysdb_req *, void *pvt);

/* service functions */
struct ldb_context *sysdb_ctx_get_ldb(struct sysdb_ctx *ctx);
struct sysdb_ctx *sysdb_req_get_ctx(struct sysdb_req *req);

/* function to start and finish a transaction
 * After sysdb_transaction() is successfully called,
 * it *MUST* be closed with a call to sysdb_transaction_done()
 * if error is == 0 the transaction is committed otherwise it
 * is canceled and all modifications to the db are thrown away
 *
 * Transactions are serialized, no other transaction or operation can be
 * performed while a transaction is active.
 */
int sysdb_transaction(TALLOC_CTX *mem_ctx,
                      struct sysdb_ctx *ctx,
                      sysdb_req_fn_t fn, void *pvt);
void sysdb_transaction_done(struct sysdb_req *req, int error);

/* An operation blocks the transaction queue as well, but does not
 * start a transaction, normally useful only for search type calls.
 * Cannot be called within a transaction */
int sysdb_operation(TALLOC_CTX *mem_ctx,
                      struct sysdb_ctx *ctx,
                      sysdb_req_fn_t fn, void *pvt);
void sysdb_operation_done(struct sysdb_req *req);

struct ldb_dn *sysdb_user_dn(struct sysdb_ctx *ctx, void *memctx,
                             const char *domain, const char *name);
struct ldb_dn *sysdb_group_dn(struct sysdb_ctx *ctx, void *memctx,
                              const char *domain, const char *name);
struct ldb_dn *sysdb_domain_dn(struct sysdb_ctx *ctx, void *memctx,
                               const char *domain);

int sysdb_init(TALLOC_CTX *mem_ctx,
               struct tevent_context *ev,
               struct confdb_ctx *cdb,
               const char *alt_db_path,
               struct sysdb_ctx **dbctx);

/* functions to retrieve information from sysdb
 * These functions automatically starts an operation
 * therefore they cannot be called within a transaction */
int sysdb_getpwnam(TALLOC_CTX *mem_ctx,
                   struct sysdb_ctx *ctx,
                   struct sss_domain_info *domain,
                   const char *name,
                   sysdb_callback_t fn, void *ptr);

int sysdb_getpwuid(TALLOC_CTX *mem_ctx,
                   struct sysdb_ctx *ctx,
                   struct sss_domain_info *domain,
                   uid_t uid,
                   sysdb_callback_t fn, void *ptr);

int sysdb_enumpwent(TALLOC_CTX *mem_ctx,
                    struct sysdb_ctx *ctx,
                    struct sss_domain_info *domain,
                    const char *expression,
                    sysdb_callback_t fn, void *ptr);

int sysdb_getgrnam(TALLOC_CTX *mem_ctx,
                   struct sysdb_ctx *ctx,
                   struct sss_domain_info *domain,
                   const char *name,
                   sysdb_callback_t fn, void *ptr);

int sysdb_getgrgid(TALLOC_CTX *mem_ctx,
                   struct sysdb_ctx *ctx,
                   struct sss_domain_info *domain,
                   gid_t gid,
                   sysdb_callback_t fn, void *ptr);

int sysdb_enumgrent(TALLOC_CTX *mem_ctx,
                    struct sysdb_ctx *ctx,
                    struct sss_domain_info *domain,
                    sysdb_callback_t fn, void *ptr);

int sysdb_initgroups(TALLOC_CTX *mem_ctx,
                     struct sysdb_ctx *ctx,
                     struct sss_domain_info *domain,
                     const char *name,
                     sysdb_callback_t fn, void *ptr);

int sysdb_get_user_attr(TALLOC_CTX *mem_ctx,
                        struct sysdb_ctx *ctx,
                        struct sss_domain_info *domain,
                        const char *name,
                        const char **attributes,
                        sysdb_callback_t fn, void *ptr);


/* functions that modify the databse
 * they have to be called within a transaction
 * See sysdb_transaction() */
int sysdb_add_group_member(struct sysdb_req *sysreq,
                           struct ldb_dn *member_dn,
                           struct ldb_dn *group_dn,
                           sysdb_callback_t fn, void *pvt);

int sysdb_remove_group_member(struct sysdb_req *sysreq,
                              struct ldb_dn *member_dn,
                              struct ldb_dn *group_dn,
                              sysdb_callback_t fn, void *pvt);

int sysdb_delete_entry(struct sysdb_req *sysreq,
                       struct ldb_dn *dn,
                       sysdb_callback_t fn, void *pvt);

int sysdb_delete_user_by_uid(struct sysdb_req *sysreq,
                             const char *domain, uid_t uid,
                             sysdb_callback_t fn, void *pvt);

int sysdb_delete_group_by_gid(struct sysdb_req *sysreq,
                              const char *domain, gid_t gid,
                              sysdb_callback_t fn, void *pvt);

int sysdb_set_user_attr(struct sysdb_req *sysreq,
                        struct sysdb_ctx *ctx,
                        const char *domain,
                        const char *name,
                        struct sysdb_attrs *attributes,
                        sysdb_callback_t fn, void *ptr);

int sysdb_add_user(struct sysdb_req *sysreq,
                   struct sss_domain_info *domain,
                   const char *name,
                   uid_t uid, gid_t gid, const char *gecos,
                   const char *homedir, const char *shell,
                   sysdb_callback_t fn, void *pvt);

int sysdb_add_group(struct sysdb_req *sysreq,
                    struct sss_domain_info *domain,
                    const char *name, gid_t gid,
                    sysdb_callback_t fn, void *pvt);

int sysdb_set_group_gid(struct sysdb_req *sysreq,
                        struct sss_domain_info *domain,
                        const char *name, gid_t gid,
                        sysdb_callback_t fn, void *pvt);

/* legacy functions for proxy providers */

int sysdb_legacy_store_user(struct sysdb_req *sysreq,
                            const char *domain,
                            const char *name, const char *pwd,
                            uid_t uid, gid_t gid, const char *gecos,
                            const char *homedir, const char *shell,
                            sysdb_callback_t fn, void *pvt);

int sysdb_legacy_store_group(struct sysdb_req *sysreq,
                             const char *domain,
                             const char *name, gid_t gid,
                             const char **members,
                             sysdb_callback_t fn, void *pvt);

int sysdb_legacy_add_group_member(struct sysdb_req *sysreq,
                                  const char *domain,
                                  const char *group,
                                  const char *member,
                                  sysdb_callback_t fn, void *pvt);

int sysdb_legacy_remove_group_member(struct sysdb_req *sysreq,
                                     const char *domain,
                                     const char *group,
                                     const char *member,
                                     sysdb_callback_t fn, void *pvt);
#endif /* __SYS_DB_H__ */
