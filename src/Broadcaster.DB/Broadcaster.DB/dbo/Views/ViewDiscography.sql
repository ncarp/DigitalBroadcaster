
CREATE VIEW [dbo].[ViewDiscography]
AS
SELECT dbo.MusicTracks.ID, dbo.MusicTracks.ArtistID, 
    dbo.MusicTracks.Title, dbo.Artists.Name AS Artist
FROM dbo.MusicTracks INNER JOIN
    dbo.Artists ON 
    dbo.MusicTracks.ArtistID = dbo.Artists.ID
WHERE (dbo.MusicTracks.Activ = 1)



