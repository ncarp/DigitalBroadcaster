
CREATE VIEW [dbo].[ViewInstrumentals]
AS

SELECT     dbo.Instrumentals.ID, dbo.Instrumentals.TypeID, dbo.Instrumentals.ElementID, dbo.Instrumentals.LastDate, Broadcaster.dbo.MusicTracks.Title, 
                      Broadcaster.dbo.Artists.Name AS Artist, Broadcaster.dbo.MusicTracks.Mix - Broadcaster.dbo.MusicTracks.Start AS Length, Broadcaster.dbo.MusicTracks.Rythm as Rythm
FROM         dbo.Instrumentals INNER JOIN
                      Broadcaster.dbo.MusicTracks ON dbo.Instrumentals.ElementID = Broadcaster.dbo.MusicTracks.ID INNER JOIN
                      Broadcaster.dbo.Artists ON Broadcaster.dbo.MusicTracks.ArtistID = Broadcaster.dbo.Artists.ID
WHERE     (dbo.Instrumentals.TypeID = 51)

UNION (
SELECT     dbo.Instrumentals.ID, dbo.Instrumentals.TypeID, dbo.Instrumentals.ElementID, dbo.Instrumentals.LastDate, Broadcaster.dbo.Jingles.Name AS Title, 
                      Broadcaster.dbo.TypeOfJingle.Name AS Artist, Broadcaster.dbo.Jingles.Mix - Broadcaster.dbo.Jingles.Start AS Length, Broadcaster.dbo.Jingles.Rythm as Rythm
FROM         dbo.Instrumentals INNER JOIN
                      Broadcaster.dbo.Jingles ON dbo.Instrumentals.ElementID = Broadcaster.dbo.Jingles.ID INNER JOIN
                      Broadcaster.dbo.TypeOfJingle ON Broadcaster.dbo.Jingles.TypeID = Broadcaster.dbo.TypeOfJingle.ID
WHERE     (dbo.Instrumentals.TypeID = 52) )

