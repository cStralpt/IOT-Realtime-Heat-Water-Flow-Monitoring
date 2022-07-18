// Next.js API route support: https://nextjs.org/docs/api-routes/introduction
import { PrismaClient } from "@prisma/client";
const prisma = new PrismaClient();
export default async function handler(req, res) {
  const nodeMCUDatas = await prisma.nodemcu.findMany({
    orderBy: [
      {
        id: "desc",
      },
    ],
  });
  res.status(200).json(nodeMCUDatas);
}
