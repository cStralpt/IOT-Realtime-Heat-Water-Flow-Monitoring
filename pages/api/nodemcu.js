// Next.js API route support: https://nextjs.org/docs/api-routes/introduction
import { PrismaClient } from "@prisma/client";
const prisma = new PrismaClient();
export default async function handler(req, res) {
  let numberPattern = /\d+/g;

  // '29.50\r\n0\r\n222'.match( numberPattern )
  let s = new Set(req.body.toString().match(numberPattern));
  let it = s.values();
  let ndData = [];
  Array.from(it).map((d) => ndData.push(d));
  let suhu = parseFloat(`${ndData[0]}.${ndData[1]}`);
  let debitair = parseFloat(ndData[ndData.length-1]);
  const d = await prisma.nodemcu.findMany();
  // res.status(200).json({ name: "satriali" });
  // if (req.body.action === "setDatas") {
  // res.status(200).json(req.body);
  if (suhu>0) {
    await prisma.nodemcu.create({
      data: {
        suhu: JSON.stringify(suhu),
        debitair: JSON.stringify(debitair),
      },
    });
  }
  res.json({
    suhu: suhu,
    DebitAir: ndData[ndData.length-4],
  });
}
