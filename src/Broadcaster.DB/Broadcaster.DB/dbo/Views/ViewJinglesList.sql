
CREATE VIEW [dbo].[ViewJinglesList]
AS
SELECT dbo.Jingles.ID, dbo.Jingles.TypeID, dbo.Jingles.Name, 
    dbo.TypeOfJingle.Name AS Type
FROM dbo.Jingles INNER JOIN
    dbo.TypeOfJingle ON 
    dbo.Jingles.TypeID = dbo.TypeOfJingle.ID
WHERE (dbo.Jingles.Activ = 1)



