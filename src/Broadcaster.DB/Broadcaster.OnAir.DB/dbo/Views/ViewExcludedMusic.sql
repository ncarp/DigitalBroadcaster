
CREATE VIEW [dbo].[ViewExcludedMusic]
AS
SELECT dbo.[PlayLists-Contents].MusicTrackID AS ID
FROM dbo.[PlayLists-Contents] INNER JOIN
    dbo.[PlayLists-Def] ON 
    dbo.[PlayLists-Contents].ListID = dbo.[PlayLists-Def].ID
WHERE (dbo.[PlayLists-Def].Activ = 1) AND 
    (dbo.[PlayLists-Def].OnAir = 0)

