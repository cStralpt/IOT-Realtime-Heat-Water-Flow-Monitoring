-- RedefineTables
PRAGMA foreign_keys=OFF;
CREATE TABLE "new_nodemcu" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "createdAt" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "suhu" TEXT NOT NULL,
    "debitair" TEXT NOT NULL
);
INSERT INTO "new_nodemcu" ("createdAt", "debitair", "id", "suhu") SELECT "createdAt", "debitair", "id", "suhu" FROM "nodemcu";
DROP TABLE "nodemcu";
ALTER TABLE "new_nodemcu" RENAME TO "nodemcu";
PRAGMA foreign_key_check;
PRAGMA foreign_keys=ON;
